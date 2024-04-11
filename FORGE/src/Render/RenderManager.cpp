#include "RenderManager.h"
#include "RenderForge.h"
#include <iostream>
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#include <OgreRoot.h>
#include <SDL.h>
#include <OgreFileSystemLayer.h>
#include <OgreBuildSettings.h>
#include <OgreLogManager.h>
#include <OgrePlugin.h>
#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <OgreRTShaderConfig.h>
#include <OgreRTShaderExports.h>
#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreParticleSystem.h>
#include <OgreBillboardSet.h>
#include <OgreViewport.h>
#include "OgreNameGenerator.h"
#pragma warning(pop)
#include "Entity.h"
#include "Transform.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Billboard.h"
#include "ForgeError.h"

std::unique_ptr<RenderManager> RenderManager::instance = nullptr;
bool RenderManager::initialised = false;

RenderManager::RenderManager() : 
	forge(nullptr),
	root(nullptr),
	sceneManager(nullptr),
	transforms(),
	cameraNames(new Ogre::NameGenerator("Camera")),
	particleSystemsNames(new Ogre::NameGenerator("ParticleSystem")) {

}

void RenderManager::updateNodePositions() {
	for (auto&& pair : transforms) {
		if (pair.second->getNeedsUpdate()) {
			const forge::Vector3& position = pair.second->getGlobalPosition();
			pair.first->setPosition(position);
			const forge::Quaternion& rotation = pair.second->getGlobalRotation();
			pair.first->setOrientation(rotation);
			const forge::Vector3& scale = pair.second->getGlobalScale();
			pair.first->setScale(scale);
			pair.second->setNeedsUpdate(false);
		}
	}
}

RenderManager::~RenderManager() {
	delete cameraNames;
	delete particleSystemsNames;
	delete forge;
}

void RenderManager::Init() {
	instance = std::unique_ptr<RenderManager>(new RenderManager());
	initialised = true;
}

RenderManager* RenderManager::GetInstance() {
	if (initialised) return instance.get();
	return nullptr;
}

bool RenderManager::setup(std::string const& appName) {
	// Verificacion de nombre de ventana valido	
	for (char c : appName) {
		if (c == '?') {
			throwError(false, "Nombre de ventana no valido");
		}
	}
	forge = new RenderForge(appName);
	if (!forge->getInitialitation()) return false;
	root = forge->getRoot();
	// Creamos la escena
	try {
		sceneManager = root->createSceneManager();
		sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	}
	catch (std::exception e) {
		return false;
	}
	return true;
}

bool RenderManager::render() {
	if(root == nullptr) return false;
	updateNodePositions();
	return root->renderOneFrame();
}

Ogre::Entity* RenderManager::addMeshNode(Mesh* mesh) {
	if (root == nullptr) return nullptr;
	try {
		Ogre::Entity* entity = sceneManager->createEntity(mesh->getMesh());
		Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
		if (mesh->getMaterial() != "") {
			entity->setMaterialName(mesh->getMaterial());
		}
		node->attachObject(entity);
		transforms.insert({ node, mesh->getEntity()->getComponent<Transform>() });
		return entity;
	} catch (std::exception e) {
		std::cerr << "ERROR: No se ha podido cargar un mesh " << mesh->getMesh() << "\n";
		return nullptr;
	}
}

Ogre::Entity* RenderManager::updateMeshNode(Ogre::Entity* entity, Mesh* mesh) {
	// Se busca el nodo asociado a la entidad y se desvincula la entidad de �l
	Ogre::SceneNode* node = entity->getParentSceneNode();
	node->detachObject(entity);
	sceneManager->destroyEntity(entity);
	// Se crea una nueva malla con o sin material y se vincula al nodo ya existente
	Ogre::Entity* newEntity = sceneManager->createEntity(mesh->getMesh());
	if (mesh->getMaterial() != "") {
		newEntity->setMaterialName(mesh->getMaterial());
	}
	node->attachObject(entity);
	return newEntity;
}

Ogre::BillboardSet* RenderManager::addBillboardNode(Billboard* bs) {
	if (root == nullptr) return nullptr;
	try {
		Ogre::BillboardSet* set = sceneManager->createBillboardSet(bs->getSize());
		set->setDefaultDimensions(bs->getBillboardWidth(), bs->getBillboardHeight());
		Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
		if (bs->getMaterial() != "") {
			set->setMaterialName(bs->getMaterial());
		}
		node->attachObject(set);
		transforms.insert({ node, bs->getEntity()->getComponent<Transform>() });
		return set;
	}
	catch (std::exception e) {
		std::cerr << "ERROR: No se ha podido cargar un billboard " << bs->getMaterial() << "\n";
		return nullptr;
	}
}

Ogre::Camera* RenderManager::addCameraNode(Camera* camera) {
	
	if (root == nullptr) return nullptr;
	try {
		// Se crea un nodo para la camara
		Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
		// Se crea la camara con las caracteristicas especificadas
		Ogre::Camera* ogreCamera = sceneManager->createCamera(cameraNames->generate());
		ogreCamera->setNearClipDistance(camera->getNearClipDistance());
		ogreCamera->setAutoAspectRatio(camera->getAutoAspectRatio());
		node->attachObject(ogreCamera);
		Ogre::Viewport* viewport = forge->getWindow().render->addViewport(ogreCamera);
		Ogre::ColourValue value = Ogre::ColourValue(
			camera->getBackgroundColor().getX(),
			camera->getBackgroundColor().getY(),
			camera->getBackgroundColor().getZ());
		viewport->setBackgroundColour(value);
		// Se a�ade el nodo al mapa de objetos de la escena de OGRE
		transforms.insert({ node, camera->getEntity()->getComponent<Transform>() });
		return ogreCamera;
	}
	catch (std::exception e) {
		std::cerr << "ERROR: No se ha podido cargar una camara " << cameraNames->generate() << "\n";
		return nullptr;
	}
}

Ogre::Light* RenderManager::addLightNode(Light* light) {
	if (root == nullptr) return nullptr;
	try {
		// Se crea una luz del tipo requerido
		Ogre::Light* ogreLight = sceneManager->createLight(Ogre::Light::LightTypes(light->getType()));
		// Se vincula la luz a un nodo de OGRE que cuelga del nodo raiz
		Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
		node->attachObject(ogreLight);
		// Se a�ade el nodo al mapa de objetos de la escena de OGRE
		transforms.insert({ node, light->getEntity()->getComponent<Transform>() });
		return ogreLight;
	}
	catch (std::exception e) {
		std::cerr << "ERROR: No se ha podido cargar una luz " << light->getType() << "\n";
		return nullptr;
	}
}

Ogre::ParticleSystem* RenderManager::addParticleSystemNode(ParticleSystem* particleSystem) {
	if (root == nullptr) return nullptr;
	try {
		// Se vincula el sistema de particulas a un nodo de OGRE que cuelga del nodo raiz
		Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
		// Se crea el sistema de particulas
		std::string name = particleSystemsNames->generate();
		Ogre::ParticleSystem* ogreParticleSystem = sceneManager->createParticleSystem(name, particleSystem->getParticle());
		ogreParticleSystem->setEmitting(particleSystem->getEmitting());
		node->attachObject(ogreParticleSystem);
		// Se a�ade el nodo al mapa de objetos de la escena de OGRE
		transforms.insert({ node, particleSystem->getEntity()->getComponent<Transform>() });
		return ogreParticleSystem;
	}
	catch (std::exception e) {
		std::cerr << "ERROR: No se ha podido cargar un sistema de particulas " << particleSystem->getParticle() << "\n";
		return nullptr;
	}
}


Ogre::ParticleSystem* RenderManager::updateParticleSystemNode(Ogre::ParticleSystem* ogreParticleSystem, ParticleSystem* particleSystem) {
	// Se busca el nodo del que cuelga el sistema de particulas que queremos borrar
	Ogre::SceneNode* node = ogreParticleSystem->getParentSceneNode();
	node->detachObject(ogreParticleSystem);
	sceneManager->destroyEntity(ogreParticleSystem);
	// Se crea el nuevo sistema y se vincula al nodo ya existente
	Ogre::ParticleSystem* newParticleSystem = sceneManager->createParticleSystem(particleSystem->getParticle());
	newParticleSystem->setEmitting(particleSystem->getEmitting());
	node->attachObject(newParticleSystem);
	return newParticleSystem;	
}


void RenderManager::removeNode(Ogre::MovableObject* object) {
	// Se busca el nodo asociado y se elimina de la escena de OGRE y del mapa de objetos de esta
	if(root == nullptr || object == nullptr) return;
	Ogre::SceneNode* node = object->getParentSceneNode();
	node->detachObject(object);
	sceneManager->destroyEntity(object);
	sceneManager->destroySceneNode(node);
	transforms.erase(node);
}

void RenderManager::removeCamera(Ogre::Camera* camera) {
	// Se busca el nodo asociado a la camara que queremos eliminar
	Ogre::SceneNode* node = camera->getParentSceneNode();
	node->detachObject(camera);
	// MUY IMPORTANTE: se elimina el viewport de la camara
	forge->getWindow().render->removeViewport(camera->getViewport()->getZOrder());
	// Se destruyen la camara, el nodo de OGRE y la referencia a el en el mapa de la escena
	sceneManager->destroyCamera(camera);
	sceneManager->destroySceneNode(node);
	transforms.erase(node);
}
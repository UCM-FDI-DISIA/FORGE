#include "RenderManager.h"
#include "RenderForge.h"
#include "Entity.h"
#include "Transform.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Billboard.h"
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreParticleSystem.h>
#include <OgreBillboardSet.h>
#include <OgreViewport.h>
#include "OgreNameGenerator.h"

std::unique_ptr<RenderManager> RenderManager::instance = nullptr;


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

RenderManager* RenderManager::getInstance() {
	if (instance.get() != nullptr) return instance.get();
	return (instance = std::unique_ptr<RenderManager>(new RenderManager())).get();
}

void RenderManager::setup(std::string appName) {
	forge = new RenderForge(appName);
	root = forge->getRoot();

	// Creamos la escena
	sceneManager = root->createSceneManager();
	sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

bool RenderManager::render() {
	updateNodePositions();
	return root->renderOneFrame();
}

Ogre::Entity* RenderManager::addMeshNode(Mesh* mesh) {
	// Se crea una entidad de OGRE
	Ogre::Entity* entity = sceneManager->createEntity(mesh->getMesh());
	// Si la malla necesita material, se le asigna
	if (mesh->getMaterial() != "") {
		entity->setMaterialName(mesh->getMaterial());
	}
	// Se vincula la entidad a un nodo que cuelga del nodo raiz
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(entity);
	// Se añade el nodo al mapa de objetos de la escena de OGRE
	transforms.insert({node, mesh->getEntity()->getComponent<Transform>()});
	return entity;
}

Ogre::Entity* RenderManager::updateMeshNode(Ogre::Entity* entity, Mesh* mesh) {
	// Se busca el nodo asociado a la entidad y se desvincula la entidad de él
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

Ogre::BillboardSet* RenderManager::addBillboardNode(Billboard* billboardSet) {
	// Se crea un billboardSet de OGRE con las dimensiones especificadas en el componente y el material
	Ogre::BillboardSet* set = sceneManager->createBillboardSet(billboardSet->getSize());
	set->setDefaultDimensions(billboardSet->getBillboardWidth(), billboardSet->getBillboardHeight());
	if (billboardSet->getMaterial() != "") {
		set->setMaterialName(billboardSet->getMaterial());
	}
	// Se vincula el billboardSet a un nodo de OGRE que cuelga del nodo raiz
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(set);
	// Se añade el nodo al mapa de objetos de la escena de OGRE
	transforms.insert({ node, billboardSet->getEntity()->getComponent<Transform>()});
	return set;
}

Ogre::Camera* RenderManager::addCameraNode(Camera* camera) {
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
	// Se añade el nodo al mapa de objetos de la escena de OGRE
	transforms.insert({ node, camera->getEntity()->getComponent<Transform>() });
	return ogreCamera;
}

Ogre::Light* RenderManager::addLightNode(Light* light) {
	// Se crea una luz del tipo requerido
	Ogre::Light* ogreLight = sceneManager->createLight(Ogre::Light::LightTypes(light->getType()));
	// Se vincula la luz a un nodo de OGRE que cuelga del nodo raiz
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ogreLight);
	// Se añade el nodo al mapa de objetos de la escena de OGRE
	transforms.insert({ node, light->getEntity()->getComponent<Transform>() });
	return ogreLight;
}

Ogre::ParticleSystem* RenderManager::addParticleSystemNode(ParticleSystem* particleSystem) {
	// Se crea el sistema de particulas
	std::string name = particleSystemsNames->generate();
	Ogre::ParticleSystem* ogreParticleSystem = sceneManager->createParticleSystem(name, particleSystem->getParticle());
	ogreParticleSystem->setEmitting(particleSystem->getEmitting());
	// Se vincula el sistema de particulas a un nodo de OGRE que cuelga del nodo raiz
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ogreParticleSystem);
	// Se añade el nodo al mapa de objetos de la escena de OGRE
	transforms.insert({ node, particleSystem->getEntity()->getComponent<Transform>()});
	return ogreParticleSystem;
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
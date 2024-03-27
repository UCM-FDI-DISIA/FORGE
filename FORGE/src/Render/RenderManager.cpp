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
	Ogre::Entity* entity = sceneManager->createEntity(mesh->getMesh());
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	if (mesh->getMaterial() != "") {
		entity->setMaterialName(mesh->getMaterial());
	}
	node->attachObject(entity);
	transforms.insert({node, mesh->getEntity()->getComponent<Transform>()});
	return entity;
}


Ogre::Entity* RenderManager::updateMeshNode(Ogre::Entity* entity, Mesh* mesh) {
	Ogre::SceneNode* node = entity->getParentSceneNode();
	node->detachObject(entity);
	sceneManager->destroyEntity(entity);
	Ogre::Entity* newEntity = sceneManager->createEntity(mesh->getMesh());
	if (mesh->getMaterial() != "") {
		newEntity->setMaterialName(mesh->getMaterial());
	}
	node->attachObject(entity);
	return newEntity;
}

Ogre::BillboardSet* RenderManager::addBillboardNode(Billboard* bs) {
	Ogre::BillboardSet* set = sceneManager->createBillboardSet(bs->getSize());
	set->setDefaultDimensions(bs->getBillboardWidth(), bs->getBillboardHeight());
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	if (bs->getMaterial() != "") {
		set->setMaterialName(bs->getMaterial());
	}
	node->attachObject(set);
	transforms.insert({ node, bs->getEntity()->getComponent<Transform>()});
	return set;
}

Ogre::Camera* RenderManager::addCameraNode(Camera* camera) {
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
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
	transforms.insert({ node, camera->getEntity()->getComponent<Transform>() });
	return ogreCamera;
}

Ogre::Light* RenderManager::addLightNode(Light* light) {
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::Light* ogreLight = sceneManager->createLight(Ogre::Light::LightTypes(light->getType()));
	node->attachObject(ogreLight);
	transforms.insert({ node, light->getEntity()->getComponent<Transform>() });
	return ogreLight;
}

Ogre::ParticleSystem* RenderManager::addParticleSystemNode(ParticleSystem* particleSystem) {
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	std::string name = particleSystemsNames->generate();
	Ogre::ParticleSystem* ogreParticleSystem = sceneManager->createParticleSystem(name, particleSystem->getParticle());
	node->attachObject(ogreParticleSystem);
	ogreParticleSystem->setEmitting(particleSystem->getEmitting());
	transforms.insert({ node, particleSystem->getEntity()->getComponent<Transform>()});
	return ogreParticleSystem;
}


Ogre::ParticleSystem* RenderManager::updateParticleSystemNode(Ogre::ParticleSystem* ogreParticleSystem, ParticleSystem* particleSystem) {
	Ogre::SceneNode* node = ogreParticleSystem->getParentSceneNode();
	node->detachObject(ogreParticleSystem);
	sceneManager->destroyEntity(ogreParticleSystem);
	Ogre::ParticleSystem* newParticleSystem = sceneManager->createParticleSystem(particleSystem->getParticle());
	newParticleSystem->setEmitting(particleSystem->getEmitting());
	node->attachObject(newParticleSystem);
	return newParticleSystem;
}


void RenderManager::removeNode(Ogre::MovableObject* object) {
	Ogre::SceneNode* node = object->getParentSceneNode();
	node->detachObject(object);
	sceneManager->destroyEntity(object);
	sceneManager->destroySceneNode(node);
	transforms.erase(node);
}

void RenderManager::removeCamera(Ogre::Camera* camera) {
	Ogre::SceneNode* node = camera->getParentSceneNode();
	node->detachObject(camera);
	forge->getWindow().render->removeViewport(camera->getViewport()->getZOrder());
	sceneManager->destroyCamera(camera);
	sceneManager->destroySceneNode(node);
	transforms.erase(node);
}
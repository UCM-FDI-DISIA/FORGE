#include "RenderManager.h"
#include "RenderForge.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "Entity.h"
#include "Transform.h"
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
#include <iostream>
#include <OgreViewport.h>

std::unique_ptr<RenderManager> RenderManager::instance = nullptr;


RenderManager::RenderManager() : 
	forge(nullptr),
	root(nullptr),
	sceneManager(nullptr),
	transforms() {

}

RenderManager::~RenderManager() {
	delete forge;
}

RenderManager* RenderManager::getInstance() {
	if (instance.get() != nullptr) return instance.get();
	return (instance = std::unique_ptr<RenderManager>(new RenderManager())).get();
}

void RenderManager::setup(std::string appName) {
	forge = new RenderForge(appName);
	root = forge->getRoot();
	if (root == nullptr) return;
	// Creamos la escena
	sceneManager = root->createSceneManager();
	sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

bool RenderManager::render() {
	if(root == nullptr) return false;
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
	return root->renderOneFrame();
}


Ogre::Entity* RenderManager::addMeshNode(Mesh* mesh) {
	if(root == nullptr) return nullptr;
	try {
		Ogre::Entity* entity = sceneManager->createEntity(mesh->getMesh());
		Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
		if (mesh->getMaterial() != "") {
			entity->setMaterialName(mesh->getMaterial());
		}
		node->attachObject(entity);
		transforms.insert({ node, mesh->getEntity()->getComponent<Transform>() });
		return entity;
	}
	catch (std::exception e) {
		std::cerr << "ERROR: No se ha podido cargar un mesh " << mesh->getMesh() << "\n";
		return nullptr;
	}
	node->attachObject(entity);
	transforms.insert({ node, mesh->getEntity()->getComponent<Transform>() });
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

Ogre::Camera* RenderManager::addCameraNode(Camera* camera) {
	if(root == nullptr) return nullptr;
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::Camera* ogreCamera = sceneManager->createCamera(camera->getName());
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
	if (root == nullptr) return nullptr;
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::Light* ogreLight = sceneManager->createLight(Ogre::Light::LightTypes(light->getType()));
	node->attachObject(ogreLight);
	transforms.insert({ node, light->getEntity()->getComponent<Transform>() });
	return ogreLight;
}

void RenderManager::removeNode(Ogre::MovableObject* object) {
	if(root == nullptr) return;
	Ogre::SceneNode* node = object->getParentSceneNode();
	node->detachObject(object);
	sceneManager->destroyEntity(object);
	sceneManager->destroySceneNode(node);
	transforms.erase(node);
}



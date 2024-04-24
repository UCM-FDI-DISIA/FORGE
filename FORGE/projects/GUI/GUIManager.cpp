#include "GUIManager.h"
#include "RenderManager.h"

#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>

std::unique_ptr<GUIManager> GUIManager::instance = nullptr;
bool GUIManager::initialised = false;

GUIManager::GUIManager() {
	overlayManager = Ogre::OverlayManager::getSingletonPtr();
}

bool GUIManager::Init() {

}

GUIManager* GUIManager::GetInstance() {
	if (initialised) return instance.get();
	return nullptr;
}

GUIManager::~GUIManager() {

}
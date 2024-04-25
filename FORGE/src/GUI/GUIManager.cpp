#include "GUIManager.h"
//#include "RenderManager.h"

#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlaySystem.h>
#include <OgreFontManager.h>

std::unique_ptr<GUIManager> GUIManager::instance = nullptr;
bool GUIManager::initialised = false;

GUIManager::GUIManager() :
	overlaySystem(nullptr),
	overlayManager(nullptr) {
}

bool GUIManager::Init() {
	instance = std::unique_ptr<GUIManager>(new GUIManager());
	initialised = true;
	return true;
}

GUIManager* GUIManager::GetInstance() {
	if (initialised) return instance.get();
	return nullptr;
}

GUIManager::~GUIManager() {
	//delete overlaySystem;
}

bool GUIManager::setup() {
	overlaySystem = new Ogre::OverlaySystem();
	overlayManager = Ogre::OverlayManager::getSingletonPtr();
	fontManager = Ogre::FontManager::getSingletonPtr();
	numUIElements = 0;
	return true;
}

void GUIManager::cleanUp() {
	delete overlayManager;
	initialised = false;
}

bool GUIManager::update() {
	return true;
}

bool GUIManager::render() {
	return true;
}

void GUIManager::refresh() {
	
}

Ogre::Font* GUIManager::getFont(std::string const& fontName) {
	return nullptr;
}

Ogre::OverlayManager* GUIManager::getOverlayManager() {
	return overlayManager;
}

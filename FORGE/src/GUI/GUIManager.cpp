#include "GUIManager.h"
#include "RenderManager.h"
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlaySystem.h>
#include <OgreFontManager.h>
#include <OgreSceneManager.h>

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

	RenderManager::GetInstance()->getSceneManager()->addRenderQueueListener(overlaySystem);

	return true;
}

void GUIManager::cleanUp() {
	RenderManager::GetInstance()->getSceneManager()->removeRenderQueueListener(overlaySystem);
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

void GUIManager::loadFont(std::string font) {
	Ogre::FontPtr mFont = Ogre::FontManager::getSingleton().create(font, "General");
	mFont->setType(Ogre::FT_TRUETYPE);
	mFont->setSource(font);
	mFont->setParameter("size", "100");
	mFont->setParameter("resolution", "250");
	mFont->load();
}

Ogre::Font* GUIManager::getFont(std::string const& fontName) {
	return nullptr;
}

Ogre::OverlayManager* GUIManager::getOverlayManager() {
	return overlayManager;
}

std::unordered_set<std::string> GUIManager::getIds() {
	return ids;
}

#include "GUIManager.h"
#pragma warning(push)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlaySystem.h>
#include <OgreFontManager.h>
#include <OgreSceneManager.h>
#include <OgreTextureManager.h>
#include <OgreMaterialManager.h>
#include <OgreNameGenerator.h>
#pragma warning(pop)
#include "RenderManager.h"
#include "Vector4.h"

std::unique_ptr<GUIManager> GUIManager::instance = nullptr;
bool GUIManager::initialised = false;

GUIManager::GUIManager() :
	overlaySystem(nullptr),
	overlayManager(nullptr),
	fontManager(nullptr),
	textureManager(nullptr),
	materialManager(nullptr),
	resourceGroupManager(nullptr),
	renderManager(nullptr),
	overlayNames(new Ogre::NameGenerator("UI")) {
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
	delete overlayNames;
}

bool GUIManager::setup() {
	overlaySystem = new Ogre::OverlaySystem();
	overlayManager = Ogre::OverlayManager::getSingletonPtr();
	fontManager = Ogre::FontManager::getSingletonPtr();
	textureManager = Ogre::TextureManager::getSingletonPtr();
	materialManager = Ogre::MaterialManager::getSingletonPtr();
	resourceGroupManager = Ogre::ResourceGroupManager::getSingletonPtr();
	renderManager = RenderManager::GetInstance();
	
	renderManager->getSceneManager()->addRenderQueueListener(overlaySystem);

	loadFont("Saeda.ttf");

	return true;
}

void GUIManager::cleanUp() const {
	renderManager->getSceneManager()->removeRenderQueueListener(overlaySystem);
	delete overlaySystem;
	initialised = false;
}

bool GUIManager::hasFont(std::string font) {
	return fonts.find(font) != fonts.end();
}

bool GUIManager::addResource(std::string resource) {
	int resourceSize = resourceRegistry.size();
	resourceRegistry.insert(resource);
	return resourceSize != resourceRegistry.size();
}

bool GUIManager::hasResource(std::string resource) {
	return resourceRegistry.count(resource);
}

void GUIManager::deleteResource(std::string resource) {
	resourceRegistry.erase(resource);
}

bool GUIManager::update() {
	return true;
}

bool GUIManager::render() {
	return true;
}

void GUIManager::loadFont(std::string font) {
	Ogre::FontPtr mFont = fontManager->create(font, "General");
	mFont->setType(Ogre::FT_TRUETYPE);
	mFont->setSource(font);
	mFont->setParameter("size", "100");
	mFont->setParameter("resolution", "250");
	mFont->load();
	fonts.insert(font);
}

Ogre::Font* GUIManager::getFont(std::string const& fontName) {
	// return fontManager->getByName(fontName);
	return nullptr;
}

Ogre::OverlayManager* GUIManager::getOverlayManager() {
	return overlayManager;
}

Ogre::FontManager* GUIManager::getFontManager() {
	return fontManager;
}

Ogre::TextureManager* GUIManager::getTextureManager() {
	return textureManager;
}

Ogre::MaterialManager* GUIManager::getMaterialManager() {
	return materialManager;
}

std::unordered_set<std::string> GUIManager::getIds() {
	return ids;
}

std::string GUIManager::getRandomName() {
	return overlayNames->generate();
}

std::unordered_set <std::string> GUIManager::getResourceRegistry() {
	return resourceRegistry;
}

Ogre::ColourValue GUIManager::Vector4ToColorValue(forge::Vector4 const& v) {
	return Ogre::ColourValue(v.getX(), v.getY(), v.getZ(), v.getW());
}

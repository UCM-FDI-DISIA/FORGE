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
#include <OgreTechnique.h>
#pragma warning(pop)
#include "ForgeError.h"
#include "RenderManager.h"
#include "Vector4.h"
#include "Vector2.h"
#include "UIComponent.h"

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
	if (initialised) {
		throwError(false, "Ya se habia inicializado el GUIManager");
	}
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
	for (UIComponent* uic : canvas) {
		uic = nullptr;
	}
	canvas.clear();
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
	resolution = renderManager->getResolution();

	loadFont("Saeda.ttf");

	Ogre::Image* img = new Ogre::Image();
	createTextureAndMaterialFromImage(img, "default.png");
	img->freeMemory();
	delete img;

	return true;
}

void GUIManager::cleanUp() const {
	if (renderManager != nullptr) {
		renderManager->getSceneManager()->removeRenderQueueListener(overlaySystem);
	}
	if (overlaySystem != nullptr) {
		delete overlaySystem;
	}
	initialised = false;
}

bool GUIManager::hasFont(std::string const& font) {
	return fonts.find(font) != fonts.end();
}

bool GUIManager::createTextureAndMaterialFromImage(Ogre::Image* img, std::string const& _texture) {
	// Cargar imagen
	try {
		img->load(_texture, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}
	catch (Ogre::Exception e) {
		throwError(false, "No se pudo encontrar la imagen para crear la textura");
	}
	if (!hasResource(_texture)) {
		// Cargar textura a partir de la imagen
		textureManager->create(_texture, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		// Cargar material a partir de la textura
		Ogre::MaterialPtr mat = materialManager->create(_texture, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		mat->getTechnique(0)->getPass(0)->createTextureUnitState(_texture);
		mat->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

		// Anadir al registro
		addResource(_texture);
	}
	return true;
}

bool GUIManager::addResource(std::string const& resource) {
	int resourceSize = static_cast<int>(resourceRegistry.size());
	resourceRegistry.insert(resource);
	return resourceSize != resourceRegistry.size();
}

bool GUIManager::hasResource(std::string const& resource) {
	return resourceRegistry.count(resource);
}

void GUIManager::deleteResource(std::string const& resource) {
	resourceRegistry.erase(resource);
}

bool GUIManager::addCanvasElement(UIComponent* uic) {
	int canvasSize = static_cast<int>(canvas.size());
	canvas.insert(uic);
	return canvasSize != canvas.size();
}

void GUIManager::deleteCanvasElement(UIComponent* uic) {
	canvas.erase(uic);
}

void GUIManager::resizeWindow() {
	for (UIComponent* uic : canvas) {
		uic->resize(resolution, renderManager->getResolution());
	}
	resolution = renderManager->getResolution();
}

void GUIManager::loadFont(std::string const& font) {
	Ogre::FontPtr mFont = fontManager->create(font, "General");
	mFont->setType(Ogre::FT_TRUETYPE);
	mFont->setSource(font);
	mFont->setParameter("size", "100");
	mFont->setParameter("resolution", "250");
	mFont->load();
	fonts.insert(font);
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

std::unordered_set<std::string>& GUIManager::getIds() {
	return ids;
}

std::string GUIManager::getRandomName() {
	return overlayNames->generate();
}

forge::Vector2 const& GUIManager::getResolution() {
	return resolution;
}

void GUIManager::setResolution(forge::Vector2 const& newRes) {
	resolution = newRes;
}

Ogre::ColourValue GUIManager::Vector4ToColorValue(forge::Vector4 const& v) {
	return Ogre::ColourValue(v.getX(), v.getY(), v.getZ(), v.getW());
}

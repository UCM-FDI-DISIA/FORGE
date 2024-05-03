#include "Image.h"
#pragma warning(push)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreOverlayContainer.h>
#include <OgreImage.h>
#include <OgreTextureManager.h>
#include <OgreTexture.h>
#include <OgreMaterialManager.h>
#include <OgreTechnique.h>
#include <OgreException.h>
#pragma warning(pop)
#include "Serializer.h"
#include "RectTransform.h"
#include "GUIManager.h"
#include "Vector2.h"

const std::string Image::id = "Image";

void Image::createImage() {
	createPanel();
	overlayPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
	overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
	setMaterial(texture);
	createOverlay(zOrder);
}

void Image::destroyImage() {
	// Destruye de menor a mayor (material < textura < imagen < panel < Overlay)
	gui->getMaterialManager()->remove(texture);
	gui->getTextureManager()->remove(texture);
	imageSource->freeMemory();
	delete imageSource;
	gui->deleteResource(texture);
	destroyPanel();
	destroyOverlay();
	imageSource = nullptr;
}

void Image::createTextureAndMaterialFromImage() {
	// Cargar imagen
	if (imageSource == nullptr) {
		imageSource = new Ogre::Image();
	}
	imageSource->load(texture, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	// Cargar textura a partir de la imagen
	gui->getTextureManager()->create(texture, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	// Cargar material a partir de la textura
	gui->getMaterialManager()->create(texture, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME)
		->getTechnique(0)->getPass(0)->createTextureUnitState(texture);

	// Anadir al registro
	gui->addResource(texture);
}

void Image::loadAndAssign() {
	// Si la imagen no esta cargada...

	if (!gui->hasResource(texture)) {
		// ...la cargo
		createTextureAndMaterialFromImage();
	}
	// Y la asigno
	overlayPanel->setMaterialName(texture);
}

Image::Image() : UIComponent(),
	imageSource(nullptr),
	texture("default.png") {
	serializer(texture, "texture");
}

Image::~Image() {
	if (imageSource != nullptr) {
		destroyImage();
	}
}

bool Image::initComponent(ComponentData* data) {
	if (UIComponent::initComponent(data)) {
		createImage();
		return true;
	}
	return false;
}

void Image::onEnabled() {
	UIComponent::onEnabled();
	createImage();
}

void Image::onDisabled() {
	UIComponent::onDisabled();
	destroyImage();
}

forge::Vector2 Image::getSourceSize() {
	return forge::Vector2((float) imageSource->getWidth(), (float) imageSource->getHeight());
}

std::string Image::getTexture() {
	return texture;
}

unsigned int Image::getSourceWidth() {
	return static_cast<int>(imageSource->getWidth());
}

unsigned int Image::getWidth() {
	return static_cast<int>(transform->getScale().getX());
}

unsigned int Image::getSourceHeight() {
	return static_cast<int>(imageSource->getHeight());
}

unsigned int Image::getHeight() {
	return static_cast<int>(transform->getScale().getY());
}

void Image::setMaterial(std::string const& mat) {
	texture = mat;
	try {
		// Intento cargar y asignar la imagen
		loadAndAssign();
	}
	catch (Ogre::Exception e) {
		// Si no se pudo cargar la imagen, error...
		std::cerr << "ERROR: No se pudo cargar la textura '" << texture << "'.\n";
		// Y cargo y asigno la default
		texture = "default.png";
		loadAndAssign();
	}
}

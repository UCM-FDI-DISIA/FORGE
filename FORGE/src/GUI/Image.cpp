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
#include <OgreException.h>
#pragma warning(pop)
#include "Serializer.h"
#include "RectTransform.h"
#include "GUIManager.h"
#include "Vector2.h"

const std::string Image::id = "Image";

void Image::createImage() {
	overlayPanel = createPanel();
	overlayPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
	overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
	setMaterial(texture);
	overlay = createOverlay(overlayPanel, zOrder);
}

void Image::destroyImage() {
	imageSource->freeMemory();
	delete imageSource;
	imageSource = nullptr;
	destroyPanel(overlayPanel);
	destroyOverlay(overlay);
}

void Image::loadAndAssign() {
	if (imageSource == nullptr) {
		imageSource = new Ogre::Image();
	}
	if (!gui.createTextureAndMaterialFromImage(imageSource, texture)) {
		texture = "default.png";
	}
	overlayPanel->setMaterialName(texture);
}

Image::Image() :
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
	return forge::Vector2(static_cast<float>(imageSource->getWidth()), static_cast<float>(imageSource->getHeight()));
}

std::string const& Image::getTexture() {
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
	// Intento cargar y asignar la imagen
	loadAndAssign();
}
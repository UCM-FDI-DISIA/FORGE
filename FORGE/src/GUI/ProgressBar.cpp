#include "ProgressBar.h"
#pragma warning(push)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
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

const std::string ProgressBar::id = "ProgressBar";

void ProgressBar::adjust() {
	frontPanel->setDimensions(value, transform->getScale().getY());
}

void ProgressBar::createProgressBar() {
	try {
		overlayPanel = createPanel();
		backImage = new Ogre::Image();
		gui->createTextureAndMaterialFromImage(backImage, backTexture);
		overlay = createOverlay(overlayPanel, zOrder - 1);

		overlayPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
		overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());

		overlayPanel->setMaterialName(backTexture);
	}
	catch (Ogre::Exception e) {
		reportError("No se pudo cargar la textura '" << backTexture << "'");
		//overlayPanel->setMaterialName("default.png"); -> GESTIÓN DE ERRORES
	}

	try {
		elementID = gui->getRandomName();
		frontPanel = createPanel();
		frontImage = new Ogre::Image();
		gui->createTextureAndMaterialFromImage(frontImage, frontTexture);
		frontOverlay = createOverlay(frontPanel, zOrder);

		frontPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
		frontPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());

		frontPanel->setMaterialName(frontTexture);
	}
	catch (Ogre::Exception e) {
		reportError("No se pudo cargar la textura '" << frontTexture << "'");
		// GESTIÓN DE ERRORES
	}

	maxValue = transform->getScale().getX();
	setValue(value);
}

void ProgressBar::destroyProgressBar() {
	// Destruye de menor a mayor (material < textura < imagen < panel < Overlay)
	gui->getMaterialManager()->remove(backTexture);
	gui->getMaterialManager()->remove(frontTexture);
	gui->getTextureManager()->remove(backTexture);
	gui->getTextureManager()->remove(frontTexture);
	backImage->freeMemory();
	frontImage->freeMemory();
	delete backImage;
	delete frontImage;
	gui->deleteResource(backTexture);
	gui->deleteResource(frontTexture);
	destroyPanel(overlayPanel);
	destroyPanel(frontPanel);
	destroyOverlay(overlay);
	destroyOverlay(frontOverlay);
	backImage = nullptr;
	frontImage = nullptr;
}

ProgressBar::ProgressBar() :
	frontPanel(nullptr),
	frontOverlay(nullptr),
	frontTexture("default.png"),
	backTexture("default.png"),
	frontImage(nullptr),
	backImage(nullptr),
	value(0),
	maxValue(100) {
	serializer(frontTexture, "front");
	serializer(backTexture, "back");
	serializer(value, "value");
}

ProgressBar::~ProgressBar() {
	if (backImage != nullptr && frontImage != nullptr) {
		destroyProgressBar();
	}
}

bool ProgressBar::initComponent(ComponentData* data) {
	if (UIComponent::initComponent(data)) {
		createProgressBar();
		return true;
	}
	return false;
}

void ProgressBar::resize(forge::Vector2 const& prev, forge::Vector2 const& updated) {
	forge::Vector2 scale = transform->getScale();
	forge::Vector2 position = transform->getPosition();

	float factorX = updated.getX() / prev.getX();
	float factorY = updated.getY() / prev.getY();

	transform->setScale(forge::Vector2(static_cast<int>(scale.getX() * factorX),
		static_cast<int>(scale.getY() * factorY)));
	transform->setPosition(forge::Vector2(static_cast<int>(position.getX() * factorX),
		static_cast<int>(position.getY() * factorY)));

	overlayPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
	overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());
	frontPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());

	maxValue = transform->getScale().getX();
	setValue(value * factorX);
}

void ProgressBar::onEnabled() {
	UIComponent::onEnabled();
	createProgressBar();
}

void ProgressBar::onDisabled() {
	UIComponent::onDisabled();
	destroyProgressBar();
}

std::string ProgressBar::getBackTexture() {
	return backTexture;
}

std::string ProgressBar::getFrontTexture() {
	return frontTexture;
}

void ProgressBar::setValue(int v) {
	if (v < 0) {
		v = 0;
	}
	else if (v > maxValue) {
		v = maxValue;
	}
	value = v;
	adjust();
}

void ProgressBar::decrease(int v) {
	value -= v;
	if (value < 0) {
		value = 0;
	}
	adjust();
}

void ProgressBar::increase(int v) {
	value += v;
	if (value > maxValue) {
		value = maxValue;
	}
	adjust();
}

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
	switch (growth) {
		case forge::LEFT_TO_RIGHT:
			frontPanel->setDimensions(transform->getScale().getX() * value, transform->getScale().getY());
			break;
		case forge::RIGHT_TO_LEFT:
			frontPanel->setDimensions(transform->getScale().getX() * value, transform->getScale().getY());
			frontPanel->setPosition(transform->getPosition().getX() + transform->getScale().getX() * (1 - value),
				transform->getPosition().getY());
			break;
		case forge::UP_TO_DOWN:
			frontPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY() * value);
			break;
		case forge::DOWN_TO_UP:
			frontPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY() * value);
			frontPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY() +
				transform->getScale().getY() * (1 - value));
			break;
	}
}

void ProgressBar::createProgressBar() {
	try {
		overlayPanel = createPanel();
		backImage = new Ogre::Image();
		gui.createTextureAndMaterialFromImage(backImage, backTexture);
		overlay = createOverlay(overlayPanel, zOrder - 1);

		overlayPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
		overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());

		overlayPanel->setMaterialName(backTexture);
	}
	catch (Ogre::Exception e) {
		reportError("No se pudo cargar la textura '" << backTexture << "'");
		overlay = createOverlay(overlayPanel, zOrder - 1);

		overlayPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
		overlayPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());

		backTexture = "default.png";
		overlayPanel->setMaterialName(backTexture);
	}

	try {
		elementID = gui.getRandomName();
		frontPanel = createPanel();
		frontImage = new Ogre::Image();
		gui.createTextureAndMaterialFromImage(frontImage, frontTexture);
		frontOverlay = createOverlay(frontPanel, zOrder);

		frontPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
		frontPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());

		frontPanel->setMaterialName(frontTexture);
	}
	catch (Ogre::Exception e) {
		reportError("No se pudo cargar la textura '" << frontTexture << "'");
		frontOverlay = createOverlay(frontPanel, zOrder);

		frontPanel->setDimensions(transform->getScale().getX(), transform->getScale().getY());
		frontPanel->setPosition(transform->getPosition().getX(), transform->getPosition().getY());

		frontTexture = "default.png";
		frontPanel->setMaterialName(frontTexture);
	}

	setValue(value);
}

void ProgressBar::destroyProgressBar() {
	// Destruye de menor a mayor (imagen < panel < Overlay)
	backImage->freeMemory();
	frontImage->freeMemory();
	delete backImage;
	delete frontImage;
	backImage = nullptr;
	frontImage = nullptr;
	gui.deleteResource(backTexture);
	gui.deleteResource(frontTexture);
	destroyPanel(overlayPanel);
	destroyPanel(frontPanel);
	destroyOverlay(overlay);
	destroyOverlay(frontOverlay);
}

ProgressBar::ProgressBar() :
	frontPanel(nullptr),
	frontOverlay(nullptr),
	frontTexture("default.png"),
	backTexture("default.png"),
	frontImage(nullptr),
	backImage(nullptr),
	value(0),
	growth(forge::LEFT_TO_RIGHT) {
	serializer(frontTexture, "front");
	serializer(backTexture, "back");
	serializer(value, "value");
	serializer(readAux, "growth");
}

ProgressBar::~ProgressBar() {
	if (backImage != nullptr && frontImage != nullptr) {
		destroyProgressBar();
	}
}

bool ProgressBar::initComponent(ComponentData* data) {
	if (UIComponent::initComponent(data)) {
		if (readAux == "LEFT_TO_RIGHT") {
			growth = forge::LEFT_TO_RIGHT;
		}
		else if (readAux == "RIGHT_TO_LEFT") {
			growth = forge::RIGHT_TO_LEFT;
		}
		else if (readAux == "UP_TO_DOWN") {
			growth = forge::UP_TO_DOWN;
		}
		else {
			growth = forge::DOWN_TO_UP;
		}
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

	setValue(value);
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

void ProgressBar::setValue(float v) {
	if (v < 0) {
		v = 0;
	}
	else if (v > 1.0f) {
		v = 1.0f;
	}
	value = v;
	adjust();
}

void ProgressBar::decrease(float v) {
	value -= v;
	if (value < 0) {
		value = 0;
	}
	adjust();
}

void ProgressBar::increase(float v) {
	value += v;
	if (value > 1.0f) {
		value = 1.0f;
	}
	adjust();
}

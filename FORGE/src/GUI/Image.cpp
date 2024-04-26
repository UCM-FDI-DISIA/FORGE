#include "Image.h"
#pragma warning(push)
#pragma warning(disable : 26495)
#pragma warning(disable : 4251)
#include <OgreOverlayContainer.h>
#include <OgreImage.h>
#include <OgreTextureManager.h>
#include <OgreTexture.h>
#include <OgreMaterialManager.h>
#include <OgreTechnique.h>
#pragma warning(pop)
#include "Serializer.h"
#include "RectTransform.h"
#include "GUIManager.h"
#include "Vector2.h"

const std::string Image::id = "Image";

Image::Image() : UIComponent(),
	imageSource(nullptr),
	texture("def.png") {
	serializer(texture, "texture");
}

Image::~Image() {
	
}

bool Image::initComponent(ComponentData* data) {
	if (UIComponent::initComponent(data)) {
		
		createPanel();
		
		setMaterial(texture);

		createOverlay(1);

		return true;
	}
	return false;
}

void Image::update() {
	
}

void Image::createTextureAndMaterialFromImage() {
	imageSource = new Ogre::Image();
	imageSource->load(texture, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	
	gui->getTextureManager()->create(texture, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);	

	gui->getMaterialManager()->create(texture, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME)
		->getTechnique(0)->getPass(0)->createTextureUnitState(texture);
	
	gui->getResourceRegistry().insert(texture);
}

forge::Vector2 Image::getSourceSize() {
	return forge::Vector2((float) imageSource->getWidth(), (float) imageSource->getHeight());
}

std::string Image::getTexture() {
	return texture;
}

unsigned int Image::getSourceWidth() {
	return (int) imageSource->getWidth();
}

unsigned int Image::getWidth() {
	return (int) transform->getScale().getX();
}

unsigned int Image::getSourceHeight() {
	return (int) imageSource->getHeight();
}

unsigned int Image::getHeight() {
	return (int) transform->getScale().getY();
}

void Image::setMaterial(std::string const& mat) {
	texture = mat;
	if (gui->getResourceRegistry().count(mat) != 0) {
		overlayPanel->setMaterialName(mat);
	}
	else { //ESTO NO VA -> LET ME COOK QUE LE QUEDA NADA
		createTextureAndMaterialFromImage();
	}
}

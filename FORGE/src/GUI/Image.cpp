#include "Image.h"
#include <OgreOverlayContainer.h>
#include "Serializer.h"
#include "RectTransform.h"
#include "GUIManager.h"
#include "Vector2.h"

const std::string Image::id = "Image";

Image::Image() : UIComponent(),
	texture("def.png") {
	serializer(texture, "texture");
	serializer(size, "size");
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

forge::Vector2 Image::getSourceSize() {
	return sourceSize;
}

std::string Image::getTexture() {
	return texture;
}

unsigned int Image::getSourceWidth() {
	return (int) sourceSize.getX();
}

unsigned int Image::getWidth() {
	return (int) size.getX();
}

unsigned int Image::getSourceHeight() {
	return (int) sourceSize.getY();
}

unsigned int Image::getHeight() {
	return (int) size.getY();
}

void Image::setMaterial(std::string const& mat) {
	overlayPanel->setMaterialName(mat);
}

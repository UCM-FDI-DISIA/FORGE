#include "Image.h"

const std::string Image::id = "Image";

Image::Image(const char* imgId, const std::string fileName, SDL_Renderer* renderer_, forge::Vector2 imgSize,
	forge::Vector2 pos_) : UIComponent(imgId, pos_), renderer(renderer_), imageSize(imgSize) {
	//assert(renderer != nullptr);

	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (surface == nullptr)
		throw "Couldn't load image: " + fileName;

	texture = SDL_CreateTextureFromSurface(renderer_, surface);
	if (texture == nullptr) {
		SDL_FreeSurface(surface);
		throw "Couldn't convert surface to texture for image: " + fileName;
	}

	sourceSize.set(surface->w, surface->h);
	renderer = renderer_;

	// Esto da error y no debería, hay que revisarlo porque probablemente deja basura
	//SDL_FreeSurface(surface);
}

Image::~Image() {}

bool Image::update() {
	// Tamano y posicion de la ventana
	if (imageSize == forge::Vector2::ZERO) {
		imageSize = sourceSize + forge::Vector2(6, 6);
	}
	ImGui::SetNextWindowSize(imageSize + forge::Vector2(6, 6));
	ImGui::SetNextWindowPos(pos);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin(windowName, NULL, window_flags);

	ImGui::Image((void*) texture,imageSize);
	
	ImGui::PopStyleVar();
	ImGui::End();
	return true;
}

void Image::setSize(forge::Vector2 size) {
	imageSize = size;
}

forge::Vector2 Image::getSize() {
	return imageSize;
}

forge::Vector2 Image::getSourceSize() {
	return sourceSize;
}

SDL_Texture* Image::getTexture() {
	return texture;
}

unsigned int Image::getSourceWidth() {
	return sourceSize.getX();
}

unsigned int Image::getWidth() {
	return imageSize.getX();
}

unsigned int Image::getSourceHeight() {
	return sourceSize.getY();
}

unsigned int Image::getHeight() {
	return imageSize.getY();
}
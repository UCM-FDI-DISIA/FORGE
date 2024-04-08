#include "Image.h"

const std::string Image::id = "Image";

Image::Image(const char* imgId, const std::string fileName, SDL_GLContext renderer_, forge::Vector2 imgSize,
	forge::Vector2 pos_) : UIComponent(imgId, pos_), renderer(renderer_), imageSize(imgSize) {
	//assert(renderer != nullptr);

	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (!surface) {
		printf("Error loading image: %s\n", SDL_GetError());
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

	//SDL_FreeSurface(surface);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	sourceSize.set((float) surface->w, (float) surface->h);
}

Image::~Image() {
	// Esto da error y no debería, hay que revisarlo porque probablemente deja basura
	SDL_FreeSurface(surface);
}

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
	return (int) sourceSize.getX();
}

unsigned int Image::getWidth() {
	return (int) imageSize.getX();
}

unsigned int Image::getSourceHeight() {
	return (int) sourceSize.getY();
}

unsigned int Image::getHeight() {
	return (int) imageSize.getY();
}
#include "Image.h"
#include "Serializer.h"
#include "SDL_image.h"
#include <imgui.h>
#include <SDL_opengl.h>
#include "GUIManager.h"
#include "RectTransform.h"

const std::string Image::id = "Image";

Image::Image() : UIComponent(),
	surface(nullptr),
	texture(0),
	renderer(GUIManager::GetInstance()->getRenderer()) {
	serializer(fileName, "fileName");
	serializer(size, "size");
}

Image::~Image() {
	// Esto da error y no debería, hay que revisarlo porque probablemente deja basura
	//SDL_FreeSurface(surface);
}

bool Image::initComponent(ComponentData* data) {
	if (UIComponent::initComponent(data)) {
		if (renderer != nullptr) {
			SDL_Surface* surface = IMG_Load(fileName.c_str());
			if (surface == nullptr) {
				std::cerr << "ERROR: No se pudo cargar la imagen de " + fileName + " \n";
			}

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

			sourceSize.set((float)surface->w, (float)surface->h);

			if (size == forge::Vector2::ZERO) {
				size = sourceSize + forge::Vector2(6, 6);
			}

			//SDL_FreeSurface(surface);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			return true;
		}

		//if (renderer != nullptr) {
		//	surface = IMG_Load(fileName.c_str());
		//	if (surface == nullptr) {
		//		std::cerr << "ERROR: No se pudo cargar la imagen de " + fileName + " \n";
		//	}
		//	else {
		//		//texture = SDL_CreateTextureFromSurface(renderer, surface);
		//		if (texture == nullptr) {
		//			//SDL_FreeSurface(surface);
		//			std::cerr << "ERROR: No se pudo cargar la imagen de " + fileName + " \n";
		//		}
		//		else {
		//			sourceSize.set((float)surface->w, (float)surface->h);

		//			if (size == forge::Vector2::ZERO) {
		//				size = sourceSize + forge::Vector2(6, 6);
		//			}

		//			return true;
		//		}
		//	}
		//}
		else {
			std::cerr << "ERROR: Debe existir un renderer para crear una imagen\n";
		}
	}
	return false;
}

void Image::update() {
	// Tamano y posicion de la ventana
	ImGui::SetNextWindowSize(gui->Vector2ToGUI(size * transform->getScale() + forge::Vector2(6, 6)));
	ImGui::SetNextWindowPos(gui->Vector2ToGUI(transform->getPosition()));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin(windowName, NULL, window_flags);

	ImGui::Image((void*)(intptr_t) texture, gui->Vector2ToGUI(size));
	
	ImGui::PopStyleVar();
	ImGui::End();
}

void Image::setSize(forge::Vector2 size_) {
	size = size_;
}

forge::Vector2 Image::getSourceSize() {
	return sourceSize;
}

GLuint Image::getTexture() {
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
#include "ImageButton.h"
#include "Serializer.h"
#include "SDL_image.h"
#include <imgui.h>
#include "GUIManager.h"
#include "RectTransform.h"

const std::string ImageButton::id = "ImageButton";

ImageButton::ImageButton() : BaseButton(),
	idleFile(""),
	hoverFile(""),
	imagesBool(false) {
	serializer(idleFile, "idleFile");
	serializer(hoverFile, "hoverFile");
	serializer(size, "size");
}

ImageButton::~ImageButton() { 
	for (SDL_Texture* i : images)  {
		delete(i);
	}
	images.clear();
}

bool ImageButton::initComponent(ComponentData* data) {
	if (BaseButton::initComponent(data)) {
		imagesBool = (hoverFile != "");
		if (createImage(idleFile, IDLE)) {
			if (imagesBool) {
				return createImage(hoverFile, HOVER);
			}
			return true;
		}
	}
	return false;

}

bool ImageButton::createImage(std::string file, ButtonState state) {
	SDL_Renderer* renderer = GUIManager::GetInstance()->getRenderer();
	if (renderer != nullptr) {
		SDL_Surface* surface = IMG_Load(file.c_str());
		if (surface == nullptr) {
			std::cerr << "No se pudo cargar la imagen de " + file + " \n";
		}
		else {
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			if (texture == nullptr) {
				SDL_FreeSurface(surface);
				std::cerr << "No se pudo cargar la imagen de " + file + " \n";
			}
			else {
				if (size == forge::Vector2::ZERO) {
					size = forge::Vector2((float)surface->w, (float)surface->h)+forge::Vector2(6, 6);
				}

				images.push_back(texture);

				return true;
			}
		}
	}
	else {
		std::cerr << "Debe existir un renderer para crear una imagen\n";
	}
	return false;
}

void ImageButton::update() {
	// Tamano y posicion de la ventana
	ImGui::SetNextWindowSize(gui->Vector2ToGUI(size + forge::Vector2(6, 6)));
	ImGui::SetNextWindowPos(gui->Vector2ToGUI(transform->getPosition()));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin(windowName, NULL, window_flags);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0));

	if (imagesBool) {
		if (ImGui::IsWindowHovered() && !pressed) {
			pressed = ImGui::ImageButton(buttonId, (void*) images[HOVER], gui->Vector2ToGUI(size));
		}
		else {
			pressed = ImGui::ImageButton(buttonId, (void*)images[IDLE], gui->Vector2ToGUI(size));
		}
	}

	else {
		if (realPos != transform->getPosition() && realPos != (realPos + ((size - (size * 0.99f)) / 4))) {
			realPos = transform->getPosition();
		}

		if (ImGui::IsWindowHovered() && !pressed) {
			pressed = ImGui::ImageButton((void*) images[IDLE], gui->Vector2ToGUI(size * 0.99f));
			if (transform->getPosition() == realPos) {
				transform->setPosition(transform->getPosition() + ((size - (size * 0.99f)) / 4));
			}
		}
		else {
			pressed = ImGui::ImageButton((void*) images[IDLE], gui->Vector2ToGUI(size));
			transform->setPosition(realPos);
		}
	}

	if (pressed) {
		mainFunc = function;
	}

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();
	ImGui::End();
}
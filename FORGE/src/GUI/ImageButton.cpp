#include "ImageButton.h"
#include <iostream>

const std::string ImageButton::id = "ImageButton";

ImageButton::ImageButton(const char* imgButId, const std::string idleFile, const std::string hoverFile,
	const std::string pressedFile, SDL_Renderer* renderer_, forge::Vector2 size_, forge::Vector2 pos_)
	: UIComponent(imgButId, pos_), imgButtonId(imgButId), pressed(false), imageButtonSize(size_), realPos(pos), imagesBool(true) {

	images.push_back(new Image(imgButId + (char) IDLE, idleFile, renderer_, size_, pos_));
	images.push_back(new Image(imgButId + (char) HOVER, hoverFile, renderer_, size_, pos_));
	images.push_back(new Image(imgButId + (char) PRESSED, pressedFile, renderer_, size_, pos_));
}

ImageButton::ImageButton(const char* imgButId, const std::string fileName, SDL_Renderer* renderer_, forge::Vector2 size_, forge::Vector2 pos_)
	: UIComponent(imgButId, pos_), imgButtonId(imgButId), pressed(false), imageButtonSize(size_), realPos(pos), imagesBool(false) {
	images.push_back(new Image(imgButId + (char)IDLE, fileName, renderer_, size_, pos_));
}

ImageButton::~ImageButton() { }

bool ImageButton::update() {
	// Tamano y posicion de la ventana
	if (imageButtonSize == forge::Vector2::ZERO) {
		for (Image* i : images) {
			i->setSize(i->getSourceSize());
		}
		imageButtonSize = images[0]->getSize() + forge::Vector2(6, 6);
	}

	ImGui::SetNextWindowSize(imageButtonSize + forge::Vector2(6, 6));
	ImGui::SetNextWindowPos(pos);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin(windowName, NULL, window_flags);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0));

	if (imagesBool) {
		if (ImGui::IsWindowHovered() && !pressed) {
			pressed = ImGui::ImageButton(imgButtonId, (void*)images[HOVER]->getTexture(), imageButtonSize);
		}
		else if (pressed) {
			pressed = ImGui::ImageButton(imgButtonId, (void*)images[PRESSED]->getTexture(), imageButtonSize);
		}
		else {
			pressed = ImGui::ImageButton(imgButtonId, (void*)images[IDLE]->getTexture(), imageButtonSize);
		}
	}

	else {
		if (ImGui::IsWindowHovered() && !pressed) {
		pressed = ImGui::ImageButton((void*)images[IDLE]->getTexture(), imageButtonSize * 0.99);
		if (pos == realPos) {
			pos = pos + ((imageButtonSize - (imageButtonSize * 0.99)) / 4);
		}
	}
	else {
		pressed = ImGui::ImageButton((void*)images[IDLE]->getTexture(), imageButtonSize);
		pos = realPos;
	}
	}

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();
	ImGui::End();
	return true;
}

bool ImageButton::isPressed() {
	return pressed;
}

void ImageButton::setPosition(forge::Vector2 pos_) {
	pos = realPos = pos_;
}

void ImageButton::setSize(forge::Vector2 size) {
	imageButtonSize = size;
}
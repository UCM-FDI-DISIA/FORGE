#include "ImageButton.h"
#include <iostream>

const std::string ImageButton::id = "ImageButton";

ImageButton::ImageButton(const char* imgButId, const std::string idleFile, const std::string hoverFile,
	const std::string pressedFile, SDL_Renderer* renderer_, std::function<void(void)> funct, forge::Vector2 size_, forge::Vector2 pos_)
	: BaseButton(imgButId, funct, size_, pos_), realPos(pos), imagesBool(true) {

	images.push_back(new Image(imgButId + (char) IDLE, idleFile, renderer_, size_, pos_));
	images.push_back(new Image(imgButId + (char) HOVER, hoverFile, renderer_, size_, pos_));
	//images.push_back(new Image(imgButId + (char) PRESSED, pressedFile, renderer_, size_, pos_));
}

ImageButton::ImageButton(const char* imgButId, const std::string fileName, SDL_Renderer* renderer_, std::function<void(void)> funct,
	forge::Vector2 size_, forge::Vector2 pos_) : BaseButton(imgButId, funct, size_, pos_), realPos(pos), imagesBool(false) {
	
	images.push_back(new Image(imgButId + (char)IDLE, fileName, renderer_, size_, pos_));
}

ImageButton::~ImageButton() { }

bool ImageButton::update() {
	// Tamano y posicion de la ventana
	if (buttonSize == forge::Vector2::ZERO) {
		for (Image* i : images) {
			i->setSize(i->getSourceSize());
		}
		buttonSize = images[0]->getSize() + forge::Vector2(6, 6);
	}

	ImGui::SetNextWindowSize(buttonSize + forge::Vector2(6, 6));
	ImGui::SetNextWindowPos(pos);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin(windowName, NULL, window_flags);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0));

	if (imagesBool) {
		if (ImGui::IsWindowHovered() && !pressed) {
			pressed = ImGui::ImageButton(buttonId, (void*)images[HOVER]->getTexture(), buttonSize);
		}
		/*else if (pressed) {
			pressed = ImGui::ImageButton(buttonId, (void*)images[PRESSED]->getTexture(), buttonSize);
		}*/
		else {
			pressed = ImGui::ImageButton(buttonId, (void*)images[IDLE]->getTexture(), buttonSize);
		}
	}

	else {
		if (ImGui::IsWindowHovered() && !pressed) {
			pressed = ImGui::ImageButton((void*)images[IDLE]->getTexture(), buttonSize * 0.99);
			if (pos == realPos) {
				pos = pos + ((buttonSize - (buttonSize * 0.99)) / 4);
			}
		}
		else {
			pressed = ImGui::ImageButton((void*)images[IDLE]->getTexture(), buttonSize);
			pos = realPos;
		}
	}

	if (pressed) {
		mainFunc = function;
	}

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();
	ImGui::End();
	return true;
}

void ImageButton::setPosition(forge::Vector2 pos_) {
	pos = realPos = pos_;
}
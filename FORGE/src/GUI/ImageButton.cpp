#include "ImageButton.h"

const std::string ImageButton::id = "ImageButton";

ImageButton::ImageButton(const char* imgButId, const std::string fileName, SDL_Renderer* renderer_, forge::Vector2 size_,
		forge::Vector2 pos_) : Image(imgButId, fileName, renderer_, size_, pos_), pressed(false), realPos(pos) {
	//ImGui::GetWindowDrawList()->AddImage()
}

ImageButton::~ImageButton() {}

bool ImageButton::update() {
	// Tamano y posicion de la ventana
	if (imageSize == forge::Vector2::ZERO) {
		imageSize = forge::Vector2(srcWidth, srcHeight);
	}
	ImGui::SetNextWindowSize(imageSize);
	ImGui::SetNextWindowPos(pos);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin(windowName, NULL, window_flags);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0));
	if (ImGui::IsWindowHovered() && !pressed) {
		pressed = ImGui::ImageButton((void*)texture, imageSize*0.98);
		if(pos == realPos)pos = pos + ((imageSize - (imageSize * 0.98))/2);
	}
	else 
	{ 
		pressed = ImGui::ImageButton((void*)texture, imageSize); 
		pos = realPos;
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
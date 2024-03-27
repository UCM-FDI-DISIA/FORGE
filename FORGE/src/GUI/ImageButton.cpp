#include "ImageButton.h"

const std::string ImageButton::id = "ImageButton";

ImageButton::ImageButton(const char* imgButId, const std::string fileName, SDL_Renderer* renderer_, forge::Vector2 size_,
		forge::Vector2 pos_) : Image(imgButId, fileName, renderer_, size_, pos_), pressed(false) {
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

	pressed = ImGui::ImageButton((void*)texture, imageSize);

	ImGui::PopStyleVar();
	ImGui::End();
	return true;
}

bool ImageButton::isPressed() {
	return pressed;
}
#include "InputText.h"

const std::string InputText::id = "InputText";

InputText::InputText(const char* textId, const char* text_, forge::Vector2 pos_) : 
    Text(textId, text_, pos_), textToChange(nullptr), textID(textId), textToWrite("") {

}

InputText::InputText(const char* textId, const char* text_, Text* textToChange_, forge::Vector2 pos_): 
    Text(textId, text_, pos_), textToChange(textToChange_), textID(textId), textToWrite("") {

}

InputText::~InputText() {
	if (textToChange != nullptr) 
	{ 
		delete(textToChange); 
	}
}

bool InputText::update() {
    // Tamano y posicion de la ventana
    if (size == forge::Vector2::ZERO) {
        ImVec2 textSize = ImGui::CalcTextSize(text);
        ImGui::SetNextWindowSize(ImVec2(textSize.x * 3.0f, textSize.y));
    }
    else {
        ImGui::SetNextWindowSize(size);
    }
    ImGui::SetNextWindowPos(pos);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, bgColor);
    ImGui::Begin(windowName, NULL, window_flags);
    // Texto con fuente cargada
    if (font != nullptr) {
        ImGui::PushFont(font);
        ImGui::InputTextWithHint(" ", text, textToWrite, IM_ARRAYSIZE(textToWrite));
        ImGui::PopFont();
    }
    else {
        ImGui::InputTextWithHint(" ", text, textToWrite, IM_ARRAYSIZE(textToWrite));
        ImGui::SetWindowFontScale(1);
    }
    if (textToWrite[0] != '\0' && textToChange != nullptr) {
        textToChange->changeText(textToWrite);
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::End();
    return true;
}
#include "InputText.h"
#include "Serializer.h"
#include "Scene.h"
#include "Entity.h"
#include <imgui.h>
#include "GUIManager.h"
#include "RectTransform.h"

const std::string InputText::id = "InputText";

InputText::InputText() : Text(),
    textToChange(nullptr),
    textToWrite("") {
    text = "Introduce tu nombre";
    serializer(text, "text");
}

InputText::~InputText() {
	
}

bool InputText::initComponent(ComponentData* data) {
    if (Text::initComponent(data)) {
        if (data->has("textToChange")) {
            std::string handler = data->get<std::string>("textToChange");
            textToChange = scene->getEntityByHandler(handler)->getComponent<Text>();
        }
        return true;
    }
    return false;
}

void InputText::update() {
    // Tamano y posicion de la ventana
    ImGui::SetNextWindowSize(gui->Vector2ToGUI(size));
    ImGui::SetNextWindowPos(gui->Vector2ToGUI(transform->getPosition()));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, gui->Vector4ToGUI(bgColor));
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
}
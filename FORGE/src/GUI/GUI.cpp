#include "GUI.h"

std::unique_ptr<GUI> GUI::instance = nullptr;

GUI::GUI() : fontLoader(ImGui::GetIO()) {}

GUI::~GUI(){}

GUI* GUI::getInstance() {
    if (instance.get() != nullptr) return instance.get();
    return (instance = std::unique_ptr<GUI>(new GUI())).get();
}

void GUI::createText(const char* textId, const char * text, forge::Vector2 pos, Vector4 color, std::string fontName) {
    if (ids.count(textId)) {
        #ifdef _DEBUG
            std::cerr << "El id " + (std::string) textId + " ya existe\n";
        #endif // _DEBUG
            return;
    }

    // Flags
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    window_flags |= ImGuiWindowFlags_NoBackground;
    
    // Tamano y posicion de la ventana
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImGui::SetNextWindowSize(ImVec2(textSize.x * 1.07f, textSize.y));
    ImGui::SetNextWindowPos(ImVec2(pos.getX(), pos.getY()));
    
    ids.insert(textId);

    ImGui::Begin(textId, NULL, window_flags);
    
    // Texto con fuente cargada
    if (fontName != "" && fonts.count(fontName)) {
        ImGui::PushFont(fonts[fontName]);
        ImGui::TextColored(ImVec4(color.x, color.y, color.z, color.w), text);
        ImGui::PopFont();
    }
    else {
        ImGui::TextColored(ImVec4(color.x, color.y, color.z, color.w), text);
        ImGui::SetWindowFontScale(1);
    }
    
    ImGui::End();
}

void GUI::loadFont(std::string name, const char* fontFile, float size) {
    if (!fonts.count(name)) {
        ImFont* font = fontLoader.Fonts->AddFontFromFileTTF(fontFile, size);
        fonts.insert({ name, font });
        #ifdef _DEBUG
            std::cout << "La fuente " + name + " se ha cargado\n";
        #endif // _DEBUG
    }
    else {
        #ifdef _DEBUG
            std::cout << "La fuente " + name + " ya esta añadida\n";
        #endif // _DEBUG
    }
}

void GUI::showLoadedFonts() {
    std::cout << "Fuentes cargadas:\n";
    for (auto f : fonts) {
        std::cout << f.first << "\n";
    }
}

void GUI::freeIds() {
    ids.clear();
}
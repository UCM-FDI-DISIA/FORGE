#include "GUI.h"

std::unique_ptr<GUI> GUI::instance = nullptr;

GUI::GUI() : fontLoader(ImGui::GetIO()) {}

GUI::~GUI(){}

GUI* GUI::getInstance() {
    if (instance.get() != nullptr) return instance.get();
    return (instance = std::unique_ptr<GUI>(new GUI())).get();
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
        std::cout << "- " << f.first << "\n";
    }
}

void GUI::freeIds() {
    ids.clear();
}

std::unordered_map<std::string, ImFont*> GUI::getFonts() {
    return fonts;
}
std::unordered_set<std::string> GUI::getIds() {
    return ids;
}
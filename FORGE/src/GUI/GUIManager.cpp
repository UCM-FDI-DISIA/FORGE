#include "GUIManager.h"

std::unique_ptr<GUIManager> GUIManager::instance = nullptr;

GUIManager::GUIManager() :  io(nullptr), renderer(nullptr), window(nullptr) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); // Initialize io in the constructor
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
}

GUIManager::~GUIManager(){
    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void GUIManager::setContext(SDL_Renderer* rend, SDL_Window* win) {
    renderer = rend;
    window = win;

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

GUIManager* GUIManager::getInstance() {
    if (instance.get() != nullptr) return instance.get();
    return (instance = std::unique_ptr<GUIManager>(new GUIManager())).get();
}

// HABLAR SOBRE COMO SE CARGARÍAN DESDE LUA
void GUIManager::loadFont(std::string name, const char* fontFile, float size) {
    if (!fonts.count(name)) {
        ImFont* font = io->Fonts->AddFontFromFileTTF(fontFile, size);
        fonts.insert({ name, font });
        #ifdef _DEBUG
            std::cout << "La fuente " + name + " se ha cargado\n";
        #endif // _DEBUG
    }
    else {
        #ifdef _DEBUG
            std::cout << "La fuente " + name + " ya esta anadida\n";
        #endif // _DEBUG
    }
}

void GUIManager::showLoadedFonts() {
    std::cout << "Fuentes cargadas:\n";
    for (auto f : fonts) {
        std::cout << "- " << f.first << "\n";
    }
}

void GUIManager::freeIds() {
    ids.clear();
}

std::unordered_map<std::string, ImFont*> GUIManager::getFonts() {
    return fonts;
}
std::unordered_set<std::string> GUIManager::getIds() {
    return ids;
}

SDL_Renderer* GUIManager::getRenderer() {
    return renderer;
}

SDL_Window* GUIManager::getWindow() {
    return window;
}

ImGuiIO* GUIManager::getIO() {
    return io;
}

bool GUIManager::update() {
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    return true;
}

bool GUIManager::render() {
    // Rendering
    ImGui::Render();
    SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
    //SDL_SetRenderDrawColor(renderer, (Uint8)(255), (Uint8)(255), (Uint8)(255), (Uint8)(255));
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
    return true;
}

void GUIManager::refresh() {
    freeIds();
}
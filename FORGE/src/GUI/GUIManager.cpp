#include "GUIManager.h"
#include <imgui.h>
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "RenderForge.h"
#include "RenderManager.h"
#include <OgreRenderWindow.h>

std::unique_ptr<GUIManager> GUIManager::instance = nullptr;
bool GUIManager::initialised = false;

bool GUIManager::Init() {
    instance = std::unique_ptr<GUIManager>(new GUIManager());
    initialised = instance->setContext();
    return initialised;
}

GUIManager::GUIManager() : renderer(nullptr), window(nullptr) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; // Initialize io in the constructor
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    //io->Fonts->AddFontDefault();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
}

GUIManager::~GUIManager(){
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

bool GUIManager::setContext() {
    //window = RenderManager::GetInstance()->getRenderForge()->getWindow().native;
    renderer = RenderManager::GetInstance()->getRenderForge()->getWindow().render;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("ventanaPrueba", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, window_flags);
    
    if (window != nullptr && renderer != nullptr) {
        /*void* glContext = nullptr;
        renderer->getCustomAttribute("GLCONTEXT", &glContext);*/
        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, glContext);
        if (glContext != nullptr) {
            ImGui_ImplSDL2_InitForOpenGL(window, glContext);
            ImGui_ImplOpenGL3_Init("#version 330");
            SDL_GL_SetSwapInterval(1);
            return true;
        }
        else {
            std::cerr << "ERROR: No hay contexto de OpenGL";
        }
    }
    else {
        std::cerr << "ERROR: La ventana y el renderer deben existir para poder crear la interfaz";
    }
    return false;
}

GUIManager* GUIManager::GetInstance() {
    if (initialised) return instance.get();
    return nullptr;
}

void GUIManager::loadFont(std::string name, const char* fontFile, float size) {
    if (!fonts.count(name)) {
        ImFont* font = ImGui::GetIO().Fonts->AddFontFromFileTTF(fontFile, size);
        fonts.insert({ name, font });
        if (font != nullptr) {
            std::cout << "La fuente " + name + " se ha cargado\n";
            return;
        }
    }
    std::cout << "La fuente " + name + " ya esta anadida\n";
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

Ogre::RenderWindow* GUIManager::getRenderer() {
    return renderer;
}

SDL_Window* GUIManager::getWindow() {
    return window;
}

bool GUIManager::update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    return true;
}

bool GUIManager::render() {
    ImGui::Render();
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
    return true;
}

void GUIManager::refresh() {
    freeIds();
}

const ImVec2& GUIManager::Vector2ToGUI(const forge::Vector2& v) const {
    return ImVec2(v.getX(), v.getY());
}

const ImVec4& GUIManager::Vector4ToGUI(const forge::Vector4& v) const {
    return ImVec4(v.getX(), v.getY(), v.getZ(), v.getW());
}
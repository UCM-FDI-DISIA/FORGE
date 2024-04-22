#include "GUIManager.h"
#include "Ogre.h"
#include "OgreImGuiOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlaySystem.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RenderManager.h"

std::unique_ptr<GUIManager> GUIManager::instance = nullptr;
bool GUIManager::initialised = false;

bool GUIManager::Init() {
    instance = std::unique_ptr<GUIManager>(new GUIManager());
    initialised = true;
    return initialised;
}

GUIManager::GUIManager() :
    overlayManager(nullptr),
    imGuiOverlay(nullptr),
    sceneManager(SceneManager::GetInstance()),
    renderManager(RenderManager::GetInstance())
    {
}

GUIManager::~GUIManager(){

}

bool GUIManager::setup() {
    overlaySystem = new Ogre::OverlaySystem();
    overlayManager = Ogre::OverlayManager::getSingletonPtr();
    imGuiOverlay = new Ogre::ImGuiOverlay();

    return true;
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

bool GUIManager::update() {
    imGuiOverlay->NewFrame();
    return true;
}

bool GUIManager::render() {
    imGuiOverlay->_findVisibleObjects(
        (Ogre::Camera*)sceneManager->getScene(sceneManager->getActiveSceneId())->getEntityByHandler("camera"),
        renderManager->getSceneManager()->getRenderQueue(),
        renderManager->getRoot()->getRenderSystem()->_getViewport()
    );
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
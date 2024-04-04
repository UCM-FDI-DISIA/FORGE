// Dear ImGui: standalone example application for SDL2 + SDL_Renderer
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

// Important to understand: SDL_Renderer is an _optional_ component of SDL2.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and SDL+OpenGL on Linux/OSX.
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "GUIManager.h"
#include "Text.h"
#include "Button.h"
#include "Image.h"
#include "ImageButton.h"
#include "InputText.h"
#include <memory>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

void funcion() {
    std::cout << "funcion" << std::endl;
}

void funcionImg() {
    std::cout << "funcionImg " << std::endl;
}

// Main code
int main(int, char**) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with SDL_Renderer graphics context
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    if (window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Error creating SDL_Renderer!");
        return 0;
    }
    //SDL_RendererInfo info;
    //SDL_GetRendererInfo(renderer, &info);
    //SDL_Log("Current SDL_Renderer: %s", info.name);

   

     // Our state
    bool show_demo_window = true;
    bool show_another_window = false;

    // COMPONENTES
    int cont = 0, con1 = 0;
    // --- GUI ---
    GUIManager* gui = GUIManager::getInstance();
    gui->setContext(renderer, window);
    gui->loadFont("Supercharge", "supercharge.ttf", 60);
    gui->loadFont("Saeda", "LTSaeada-Black.otf", 60);
    gui->showLoadedFonts();
    // --- TEXT ---
    //Text* text = new Text("prueba", "Saeda", forge::Vector2(100, 200));
    //text->setBackground();
    //text->removeBackground();
    //text->setColor(forge::Vector4({ .0, 0.0, 0.0, 1.0 }));
    //text->changeTextOpacity(0.3f);
    //text->changeFont("Supercharge");
    //text->changeBackgroundOpacity(0.3f);
    //text->changeText("Texto");
    //text->setPosition(forge::Vector2(600, 100));
    // --- BUTTON ---
    //Button* button = new Button("prueba2", "hola", funcion);
    //button->setColor(forge::Vector4(0.0, 0.0, 1.0, 1.0));
    //button->changeText("Boton");
    //button->changeFont("Saeda");
    //button->changeButtonOpacity(0.5);
    //button->setPosition(forge::Vector2(100, 100));
    //// --- IMAGE ---
    //Image* img = new Image("panko", "panko.png", renderer, forge::Vector2(300, 300));
    //img->setPosition(forge::Vector2(250, 250));
    //img->setSize(forge::Vector2(200, 200));
    //// --- IMAGE BUTTON ---
    //ImageButton* imgb = new ImageButton("butImg", "idle.png", "hover.png", "pressed.png", renderer, funcionImg, forge::Vector2(632, 144));
    //imgb->setPosition(forge::Vector2(550, 250));
    ////imgb->setSize(forge::Vector2(300, 300));
    //ImageButton* imgb2 = new ImageButton("butImg2", "idle.png", renderer, funcionImg, forge::Vector2(632, 144));
    //imgb2->setPosition(forge::Vector2(550, 450));
    ////imgb2->setSize(forge::Vector2(300, 300));
    //// --- INPUTTEXT ---
    //InputText* itext = new InputText("prueba5", "Introduce texto", text, forge::Vector2(100, 600));
    //InputText* itext2 = new InputText("prueba4", "Introduce texto", forge::Vector2(100, 660));
    ////itext2->setBackground();
    ////itext2->removeBackground();
    //itext2->setColor(forge::Vector4({ 0.0, 0.0, 0.0, 1.0 }));
    // Main loop
    bool done = false;
    while (!done) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        gui->update();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
       /*if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);*/

        // Textos
        /*text->update();
        itext->update();
        itext2->update();*/

        // Botones
        /*BaseButton::resetFunction();
        button->update();
        img->update();
        imgb->update();
        imgb2->update();
        BaseButton::mainFunctionCall();*/

        gui->render();
        gui->refresh();
    }
    //delete(text);
    //delete(button);
    //delete(img);
    //delete(itext); 
    //delete(itext2);
    //delete(imgb);
    //delete(imgb2); // no da error pero no borra el surface y no deja basura
    //delete(gui); // ya se llama
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

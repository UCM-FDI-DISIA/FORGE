#pragma once

#include <memory>
#include <iostream>
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h> 
#include "Vector2.h"
#include <unordered_map>
#include <unordered_set>

class GUI {
private:
	static std::unique_ptr<GUI> instance;

	ImGuiIO& fontLoader;

	std::unordered_map<std::string, ImFont*> fonts;
	std::unordered_set<std::string> ids;

	// TENEMOS QUE AÑADIR UN PUNTERO AL RENDERER Y UN GETRENDERER PARA LAS IMÁGENES

public:
	struct Vector4 { float x, y, z, w; };
	static GUI* getInstance();
	GUI();
	~GUI();

	void loadFont(std::string name, const char* fontFile, float size);
	
	void showLoadedFonts();

	void freeIds();

	std::unordered_map<std::string, ImFont*> getFonts();
	std::unordered_set<std::string> getIds();
};
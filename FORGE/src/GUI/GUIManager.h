#pragma once

#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include <imgui.h>
#include <SDL.h> 
#include <iostream>
#include <unordered_map>
#include <unordered_set>

class GUIManager {
private:
	// Instancia Singleton
	static std::unique_ptr<GUIManager> instance;

	// Input/Output (Input: controles, fuentes Output: graficos)
	ImGuiIO* io;

	// Mapa desordenado de fuentes
	std::unordered_map<std::string, ImFont*> fonts;

	// Mapa desordenado de identificadores 
	std::unordered_set<std::string> ids;

	// Renderer de SDL
	SDL_Renderer* renderer;

	// Ventana de SDL
	SDL_Window* window;

public:
	static GUIManager* getInstance();

	/// <summary>
	/// Constructora de la clase GUI
	/// </summary>	
	GUIManager();

	/// <summary>
	/// Destructora por defecto de la clase GUI
	/// </summary>	
	~GUIManager();

	/// <summary>
	/// Asigna las variables de render
	/// </summary>	
	/// <param name = "rend">Renderer de SDL</param>
	/// <param name = "win">Ventana de SDL</param>
	void setContext(SDL_Renderer* rend, SDL_Window* win);

	/// <summary>
	/// Carga una fuente
	/// </summary>	
	/// <param name = "name">Identificador de la fuente</param>
	/// <param name = "fontFile">Nombre del archivo (fuente)</param>
	/// <param name = "size">Tamano de la fuente</param>
	void loadFont(std::string name, const char* fontFile, float size);
	
	/// <summary>
	/// Muestra las fuentes cargadas
	/// </summary>	
	void showLoadedFonts();

	/// <summary>
	/// Libera todos los identificadores guardados
	/// </summary>	
	void freeIds();

	/// <summary>
	/// Devuelve el mapa desordenado de fuentes cargadas
	/// </summary>	
	/// <returns>El mapa desordenado de fuentes cargadas</returns>
	std::unordered_map<std::string, ImFont*> getFonts();

	/// <summary>
	/// Devuelve el mapa desordenado de identificadores guardados
	/// </summary>	
	/// <returns>El mapa desordenado de identificadores guardados</returns>
	std::unordered_set<std::string> getIds();

	/// <summary>
	/// Devuelve el renderer de SDL
	/// </summary>	
	/// <returns>El renderer de SDL</returns>
	SDL_Renderer* getRenderer();

	/// <summary>
	/// Devuelve la ventana de SDL
	/// </summary>	
	/// <returns>La ventana de SDL</returns>
	SDL_Window* getWindow();

	/// <summary>
	/// Devuelve el Input/Output
	/// </summary>	
	/// <returns>El Input/Output</returns>
	ImGuiIO* getIO();

	/// <summary>
	/// Actualiza los frames
	/// </summary>	
	bool update();

	/// <summary>
	/// Renderizado
	/// </summary>	
	bool render();

	/// <summary>
	/// Preparacion para el siguiente update
	/// </summary>	
	void refresh();
};
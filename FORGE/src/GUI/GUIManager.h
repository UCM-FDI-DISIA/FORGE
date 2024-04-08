#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Vector2.h"
#include "Vector4.h"

struct SDL_Renderer;
struct SDL_Window;
struct ImVec2;
struct ImVec4;
struct ImFont;

class GUIManager {
private:
	// Instancia Singleton
	static std::unique_ptr<GUIManager> instance;

	// Marcador de inicializacion
	static bool initialised;

	// Mapa desordenado de fuentes
	std::unordered_map<std::string, ImFont*> fonts;

	// Mapa desordenado de identificadores 
	std::unordered_set<std::string> ids;

	// Renderer de SDL
	SDL_Renderer* renderer;

	// Ventana de SDL
	SDL_Window* window;

public:
	static bool Init();
	static GUIManager* GetInstance();

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
	bool setContext();

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

	/// <summary>
	/// Conversor de Vector2 a ImVec2
	/// </summary>
	/// <param name = "v">Vector2 a convertir</param>
	/// <returns>ImVec2 con la informacion del Vector2</returns>
	const ImVec2& Vector2ToGUI(const forge::Vector2& v) const;

	/// <summary>
	/// Conversor de Vector4 a ImVec4
	/// </summary>
	/// <param name = "v">Vector4 a convertir</param>
	/// <returns>ImVec4 con la informacion del Vector4</returns>
	const ImVec4& Vector4ToGUI(const forge::Vector4& v) const;
};
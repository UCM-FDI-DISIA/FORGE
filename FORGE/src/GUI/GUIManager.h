#pragma once
#include <memory>
#include <unordered_set>
#include <string>

namespace Ogre {
	class OverlaySystem;
	class OverlayManager;
	class Overlay;
	class OverlayContainer;
	class FontManager;
	class Font;
}

class GUIManager {
private:
	static std::unique_ptr<GUIManager> instance;
	static bool initialised;

	// Conjunto desordenado de fuentes
	std::unordered_set<std::string> fonts;

	// Conjunto desordenado de identificadores 
	std::unordered_set<std::string> ids;

	// Sistema y manager de la interfaz de Ogre
	Ogre::OverlaySystem* overlaySystem;
	Ogre::OverlayManager* overlayManager;
	Ogre::FontManager* fontManager;

	/// <summary>
	/// Constructora de la clase GUI
	/// </summary>	
	GUIManager();

public:
	/// <summary>
	/// Crea una instancia del UIManager
	/// </summary>
	/// <returns>Si la inicializacion fue correcta</returns>
	static bool Init();
	/// <returns>Devuelve una instancia al UIManager si existe, si no existe devuelve un puntero a nulo</returns>
	static GUIManager* GetInstance();

	/// <summary>
	/// Destructora por defecto de la clase GUI
	/// </summary>	
	~GUIManager();

	/// <summary>
	/// Asigna las variables de render
	/// </summary>	
	bool setup();

	/// <summary>
	/// Elimina la memoria creada por el GUIManager
	/// </summary>
	void cleanUp();

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

	void loadFont(std::string font);

	#pragma region Getters
	/// <summary>
	/// Devuelve la fuente consultada
	/// </summary>	
	/// <returns>La fuente si existe</returns>
	Ogre::Font* getFont(std::string const& fontName);

	/// <summary>
	/// Devuelve el manager del overlay
	/// </summary>	
	/// <returns>El manager del overlay</returns>
	Ogre::OverlayManager* getOverlayManager();

	/// <summary>
	/// Devuelve el conjunto desordenado de identificadores guardados
	/// </summary>	
	/// <returns>El conjunto desordenado de identificadores guardados</returns>
	std::unordered_set<std::string> getIds();
	#pragma endregion

	#pragma region Setters

	#pragma endregion
};
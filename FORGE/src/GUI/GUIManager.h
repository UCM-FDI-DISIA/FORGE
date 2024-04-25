#pragma once
#include <memory>
#include <unordered_map>
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

	int numUIElements;

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

	#pragma region Getters
	Ogre::Font* getFont(std::string const& fontName);

	Ogre::OverlayManager* getOverlayManager();
	#pragma endregion

	#pragma region Setters

	#pragma endregion
};
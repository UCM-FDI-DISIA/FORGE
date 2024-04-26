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
	class ColourValue;
	class TextureManager;
	class MaterialManager;
	class ResourceGroupManager;
}

namespace forge {
	class Vector4;
}

class RenderManager;

class GUIManager {
private:
	static std::unique_ptr<GUIManager> instance;
	static bool initialised;

	// Conjunto desordenado de fuentes
	std::unordered_set<std::string> fonts;

	// Conjunto desordenado de identificadores 
	std::unordered_set<std::string> ids;

	// Conjunto desordenado de recursos
	std::unordered_set<std::string> resourceRegistry;

	// Managers de Ogre
	Ogre::OverlaySystem* overlaySystem;
	Ogre::OverlayManager* overlayManager;
	Ogre::FontManager* fontManager;
	Ogre::TextureManager* textureManager;
	Ogre::MaterialManager* materialManager;
	Ogre::ResourceGroupManager* resourceGroupManager;

	// Manager de renderizado
	RenderManager* renderManager;

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
	void cleanUp() const;

	/// <summary>
	/// Actualiza los frames
	/// </summary>	
	bool update();

	/// <summary>
	/// Renderizado
	/// </summary>	
	bool render();

	/// <summary>
	/// Carga una fuente en el manager de la interfaz (OverlayManager)
	/// </summary>
	/// <param name = "font">Nombre de la nueva fuente (acabado en .ttf -> "Ejemplo.ttf")</param>
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
	/// Devuelve el manager de texturas
	/// </summary>	
	/// <returns>El manager del texturas</returns>
	Ogre::TextureManager* getTextureManager();

	/// <summary>
	/// Devuelve el manager de materiales
	/// </summary>	
	/// <returns>El manager de materiales</returns>
	Ogre::MaterialManager* getMaterialManager();

	/// <summary>
	/// Devuelve el manager de recursos
	/// </summary>	
	/// <returns>El manager de recursos</returns>
	Ogre::ResourceGroupManager* getResourceManager();

	/// <summary>
	/// Devuelve el conjunto desordenado de identificadores guardados
	/// </summary>	
	/// <returns>El conjunto desordenado de identificadores guardados</returns>
	std::unordered_set<std::string> getIds();

	/// <summary>
	/// Devuelve el conjunto desordenado de recursos guardados
	/// </summary>	
	/// <returns>El conjunto desordenado de recursos guardados</returns>
	std::unordered_set<std::string> getResourceRegistry();
	#pragma endregion

	#pragma region Setters

	#pragma endregion

	/// <summary>
	/// Convierte un Vector4 en un Color Value
	/// </summary>
	/// <param name = "v">Vector4 a convertir</param>
	/// <returns>Un Ogre::ColorValue equivalente al Vector4</returns>
	Ogre::ColourValue Vector4ToColorValue(forge::Vector4 const& v);
};
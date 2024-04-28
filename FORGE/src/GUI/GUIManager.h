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
	class NameGenerator;
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

	//Generadores de nombres aleatorios
	Ogre::NameGenerator* overlayNames;

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
	/// <param name="font">Nombre de la nueva fuente (acabado en .ttf -> "Ejemplo.ttf")</param>
	/// <param name="size">Altura de la fuente nueva</param>
	/// <param name="resolution">Resolucion de la fuente nueva</param>
	void loadFont(std::string font);

	/// <summary>
	/// Comprueba si la fuente ya se a cargado (si ya existe en el conjunto (set))
	/// </summary>
	/// <param name = "font">Nombre de la fuente (acabado en .ttf -> "Ejemplo.ttf")</param>
	/// <returns>True si la fuente ya esta anadida, false si no lo esta</returns>
	bool hasFont(std::string font);

	/// <summary>
	/// Inserta un recurso en el conjunto de recursos
	/// </summary>	
	/// <returns>True si lo ha podido introducir, false si esta repetido</returns>
	bool addResource(std::string resource);

	/// <summary>
	/// Devuelve si tiene el recurso o no
	/// </summary>	
	/// <returns>True si lo tiene, false si no</returns>
	bool hasResource(std::string resource);

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
	/// Devuelve el manager del overlay
	/// </summary>	
	/// <returns>El manager del overlay</returns>
	Ogre::FontManager* getFontManager();

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
	/// Devuelve el conjunto desordenado de identificadores guardados
	/// </summary>	
	/// <returns>El conjunto desordenado de identificadores guardados</returns>
	std::unordered_set<std::string> getIds();

	/// <summary>
	/// Devuelve un nombre aleatorio nuevo generado por Ogre
	/// </summary>
	/// <returns>El nombre generado por el generador de nombres de Ogre</returns>
	std::string getRandomName();

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
#pragma once

#ifndef IMAGE_H_
#define IMAGE_H_

#include "UIComponent.h"

namespace Ogre {
	class Image;
};

namespace forge {
	class Vector2;
};

class Image : public UIComponent {
private:
	// Textura
	std::string texture;

	// Tamano original de la imagen
	Ogre::Image* imageSource;

	/// <summary>
	/// Crea la imagen con su Panel y su Overlay
	/// </summary>	
	void createImage();

	/// <summary>
	/// Destruye la imagen con su Panel y su Overlay
	/// </summary>	
	void destroyImage();

	/// <summary>
	/// Carga y guarda la imagen del componente en imageSource, creando tambien una textura y un material, y
	/// registrandola en el registro de recursos del GUIManager
	/// </summary>
	void createTextureAndMaterialFromImage();

	/// <summary>
	/// Asigna la imagen al Panel, comprobando si debe o no cargarla antes
	/// </summary>
	void loadAndAssign();

public:
	// Id de componente
	static const FORGE_API_VAR std::string id;

	/// <summary>
	/// Constructora del componente Image
	/// </summary>	
	FORGE_API Image();

	/// <summary>
	/// Destructora del componente imagen
	/// </summary>	
	FORGE_API ~Image();

	/// <summary>
	/// Inicializa la Image con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	FORGE_API bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Activa el componente (llama a crear la imagen)
	/// </summary>	
	virtual FORGE_API void onEnabled();

	/// <summary>
	/// Desactiva el componente (llama a destruir la imagen)
	/// </summary>	
	virtual FORGE_API void onDisabled();

	#pragma region Getters
	/// <summary>
	/// Devuelve el tamano original de la imagen
	/// </summary>	
	FORGE_API forge::Vector2 getSourceSize();

	/// <summary>
	/// Devuelve la textura de SDL
	/// </summary>	
	FORGE_API std::string getTexture();

	/// <summary>
	/// Devuelve el ancho de la imagen original
	/// </summary>	
	FORGE_API unsigned int getSourceWidth();

	/// <summary>
	/// Devuelve el ancho actual de la imagen
	/// </summary>	
	FORGE_API unsigned int getWidth();

	/// <summary>
	/// Devuelve el alto de la imagen original
	/// </summary>
	FORGE_API unsigned int getSourceHeight();

	/// <summary>
	/// Devuelve el alto actual de la imagen
	/// </summary>
	FORGE_API unsigned int getHeight();
	#pragma endregion

	#pragma region Setters
	/// <summary>
	/// Asigna un material (textura)
	/// </summary>
	/// <param name="mat"> Nombre del nuevo material</param>
	FORGE_API void setMaterial(std::string const& mat);
	#pragma endregion

};

#endif // !IMAGE_H_
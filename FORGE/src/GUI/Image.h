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

public:
	// Id de componente
	static const std::string id;

	/// <summary>
	/// Crea una imagen a partir de un archivo
	/// </summary>	
	Image();

	/// <summary>
	/// Destructora del componente imagen
	/// </summary>	
	virtual ~Image();

	/// <summary>
	/// Inicializa el Image con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Actualizacion de la imagen
	/// </summary>
	virtual void update();

	/// <summary>
	/// Carga y guarda la imagen del componente en imageSource, creando tambien una textura y un material, y
	/// regsitrandola en el registro de recursos del GUIManager
	/// </summary>
	void createTextureAndMaterialFromImage();

	#pragma region Getters
	/// <summary>
	/// Devuelve el tamano original de la imagen
	/// </summary>	
	forge::Vector2 getSourceSize();

	/// <summary>
	/// Devuelve la textura de SDL
	/// </summary>	
	std::string getTexture();

	/// <summary>
	/// Devuelve el ancho de la imagen original
	/// </summary>	
	unsigned int getSourceWidth();

	/// <summary>
	/// Devuelve el ancho actual de la imagen
	/// </summary>	
	unsigned int getWidth();

	/// <summary>
	/// Devuelve el alto de la imagen original
	/// </summary>
	unsigned int getSourceHeight();

	/// <summary>
	/// Devuelve el alto actual de la imagen
	/// </summary>
	unsigned int getHeight();
	#pragma endregion

	#pragma region Setters
	/// <summary>
	/// Asigna un material (textura)
	/// </summary>
	/// <param name="mat"> Nombre del nuevo material</param>
	void setMaterial(std::string const& mat);
	#pragma endregion

};

#endif // !IMAGE_H_
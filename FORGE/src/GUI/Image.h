#pragma once

#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include "UIComponent.h"
#include <Vector2.h>
#include <Vector4.h>

typedef unsigned int GLuint;
namespace Ogre {
	class RenderWindow;
}
struct ImVec2;
struct ImVec4;
struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Surface;

class Image : public UIComponent {
private:
	// Archivo
	std::string fileName;

	// Textura
	GLuint texture;

	// Tamano original de la imagen
	forge::Vector2 sourceSize;

	// Renderer de SDL
	Ogre::RenderWindow* renderer;

	// Superficie de SDL
	SDL_Surface* surface;

public:
	// Id de componente
	static const std::string id;

	/// <summary>
	/// Crea una imagen a partir de un archivo. Se aceptan varios tipos de imagen, entre ellos: PNG, JPG y SVG  
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
	/// Cambia el tamano de la imagen  
	/// </summary>	
	/// <param name = "size">Nuevo tamano</param>
	void setSize(forge::Vector2 size);

	/// <summary>
	/// Devuelve el tamano original de la imagen
	/// </summary>	
	forge::Vector2 getSourceSize();

	/// <summary>
	/// Devuelve la textura de SDL
	/// </summary>	
	GLuint getTexture();

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
};

#endif // !IMAGE_H_
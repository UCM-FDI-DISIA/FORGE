#pragma once

#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include "SDL_image.h"
#include "SDL_opengl.h"
#include "UIComponent.h"

class Image : public UIComponent {

private:
	static const std::string id;

protected:
	GLuint texture;

	forge::Vector2 sourceSize;
	forge::Vector2 imageSize;

	SDL_GLContext renderer;
	SDL_Surface* surface;

public:
	/// <summary>
	/// Crea una imagen a partir de un archivo. Se aceptan varios tipos de imagen, entre ellos: PNG, JPG y SVG  
	/// </summary>	
	/// <param name = "imgId">Identificador de la imagen (los identificadores de componetes UI NO PUEDEN COINCIDIR)</param>
	/// <param name = "fileName">Direcc�on del archivo ("C:/MyAssets/asset.png")</param>
	/// <param name = "renderer_">Renderer de SDL</param>
	/// <param name = "imgSize">Tama�o de la imagen por pantalla</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	Image(const char* imgId, const std::string fileName, SDL_GLContext renderer_, forge::Vector2 imgSize,
		forge::Vector2 pos_ = forge::Vector2::ZERO);

	/// <summary>
	/// Destructora del componente imagen
	/// </summary>	
	virtual ~Image();

	/// <summary>
	/// Actualizacion de la imagen
	/// </summary>
	virtual bool update();

	/// <summary>
	/// Cambia el tamano de la imagen  
	/// </summary>	
	/// <param name = "size">Nuevo tamano</param>
	void setSize(forge::Vector2 size);

	/// <summary>
	/// Devuelve el tama�o de la imagen
	/// </summary>	
	forge::Vector2 getSize();

	/// <summary>
	/// Devuelve el tama�o original de la imagen
	/// </summary>	
	forge::Vector2 getSourceSize();

	/// <summary>
	/// Devuelve la textura de OpenGL
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
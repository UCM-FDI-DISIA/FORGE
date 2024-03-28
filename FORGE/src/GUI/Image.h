#pragma once

#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include "SDL_image.h"
#include "UIComponent.h"

class Image : public UIComponent {

private:
	static const std::string id;

protected:
	SDL_Texture* texture;

	unsigned int srcWidth;
	unsigned int srcHeight;

	forge::Vector2 imageSize;

	SDL_Renderer* renderer;

public:
	/// <summary>
	/// Crea una imagen a partir de un archivo. Se aceptan varios tipos de imagen, entre ellos: PNG, JPG y SVG  
	/// </summary>	
	/// <param name = "imgId">Identificador de la imagen (los identificadores de componetes UI NO PUEDEN COINCIDIR)</param>
	/// <param name = "fileName">Direccíon del archivo ("C:/MyAssets/asset.png")</param>
	/// <param name = "renderer_">Renderer de SDL</param>
	/// <param name = "imgSize">Tamaño de la imagen por pantalla</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	Image(const char* imgId, const std::string fileName, SDL_Renderer* renderer_, forge::Vector2 imgSize,
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
	/// Devuelve la textura de SDL
	/// </summary>	
	SDL_Texture* getTexture();

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
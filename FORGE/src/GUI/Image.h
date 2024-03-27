#pragma once

#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include "SDL.h"
#include "UIComponent.h"

class Image : public UIComponent {
private:
	static const std::string id;

	SDL_Texture* texture;

	unsigned int srcWidth;
	unsigned int srcHeight;

	forge::Vector2 imageSize;

	SDL_Renderer* renderer;

public:
	/// <summary>
	/// Crea una imagen a partir de un archivo. Se aceptan varios tipos de imagen, entre ellos: PNG, JPG y SVG  
	/// </summary>	
	/// <param name = "imgId">Nombre de la imagen</param>
	/// <param name = "fileName">Direccíon del archivo ("C:/MyAssets/asset.png")</param>
	/// <param name = "imgSize">Tamaño de la imagen por pantalla</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	Image(const char* imgId, const std::string fileName, SDL_Renderer* renderer_, forge::Vector2 imgSize,
		forge::Vector2 pos_ = forge::Vector2::ZERO);
	~Image();

	/// <summary>
	/// Actualizacion de la imagen
	/// </summary>
	bool update();

	/// <summary>
	/// Cambia el tamaño de la imagen  
	/// </summary>	
	/// <param name = "size">Nuevo tamaño</param>
	void setSize(forge::Vector2 size);

	/// <summary>
	/// Devuelve la textura de SDL
	/// </summary>	
	SDL_Texture* getTexture() {
		return texture;
	}
	/// <summary>
	/// Devuelve el ancho de la imagen original
	/// </summary>	
	unsigned int getSourceWidth() {
		return srcWidth;
	}
	/// <summary>
	/// Devuelve el ancho actual de la imagen
	/// </summary>	
	unsigned int getWidth() {
		return imageSize.getX();
	}
	/// <summary>
	/// Devuelve el alto de la imagen original
	/// </summary>
	unsigned int getSourceHeight() {
		return srcHeight;
	}
	/// <summary>
	/// Devuelve el alto actual de la imagen
	/// </summary>
	unsigned int getHeight() {
		return imageSize.getY();
	}
};

#endif // !IMAGE_H_
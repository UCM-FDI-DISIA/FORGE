#pragma once

#ifndef IMAGEBUTTON_H_
#define IMAGEBUTTON_H_

#include "Image.h"

class ImageButton : public Image {
private:
	static const std::string id;

	bool pressed;

public:
	/// <summary>
	/// Crea un botón con una imagen a partir de un archivo. Se aceptan varios tipos de imagen, entre ellos: PNG, JPG y SVG  
	/// </summary>	
	/// <param name = "imgButId">Identificador del boton con imagen (los identificadores de componetes UI NO PUEDEN COINCIDIR)</param>
	/// <param name = "fileName">Direccíon del archivo ("C:/MyAssets/asset.png")</param>
	/// <param name = "renderer_">Renderer de SDL</param>
	/// <param name = "size_">Tamaño de la imagen por pantalla</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	ImageButton(const char* imgButId, const std::string fileName, SDL_Renderer* renderer_, forge::Vector2 size_,
		forge::Vector2 pos_ = forge::Vector2::ZERO);

	/// <summary>
	/// Destructora del componente boton con imagen
	/// </summary>	
	~ImageButton();

	/// <summary>
	/// Actualizacion del boton con imagen
	/// </summary>
	bool update() override;

	// <summary>
	/// Devuelve true si el boton esta pulsado
	/// </summary>	
	bool isPressed();
};
#endif // !IMAGEBUTTON_H_

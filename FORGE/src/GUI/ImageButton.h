#pragma once

#ifndef IMAGEBUTTON_H_
#define IMAGEBUTTON_H_

#include "BaseButton.h"
#include "Image.h"

class ImageButton : public BaseButton {
private:
	// Id de componente
	static const std::string id;

	enum ButtonState {
		IDLE, HOVER //PRESSED
	};

	std::vector<Image*> images;

	forge::Vector2 realPos;

	bool imagesBool;

public:
	/// <summary>
	/// Crea un botón con una imagen a partir de un archivo. Se aceptan varios tipos de imagen, entre ellos: PNG, JPG y SVG  
	/// </summary>	
	/// <param name = "imgButId">Identificador del boton con imagen (los identificadores de componetes UI NO PUEDEN COINCIDIR)</param>
	/// <param name = "fileName">Direccíon del archivo ("C:/MyAssets/asset.png")</param>
	/// <param name = "renderer_">Renderer de SDL</param>
	/// <param name = "size_">Tamaño de la imagen por pantalla</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	ImageButton(const char* imgButId, const std::string idleFile, const std::string hoverFile,
		const std::string pressedFile, SDL_Renderer* renderer_, std::function<void(void)> funct, forge::Vector2 size_, 
		forge::Vector2 pos_ = forge::Vector2::ZERO);

	/// <summary>
	/// Crea un botón con una imagen a partir de un archivo. Se aceptan varios tipos de imagen, entre ellos: PNG, JPG y SVG  
	/// </summary>	
	/// <param name = "imgButId">Identificador del boton con imagen (los identificadores de componetes UI NO PUEDEN COINCIDIR)</param>
	/// <param name = "fileName">Direccíon del archivo ("C:/MyAssets/asset.png")</param>
	/// <param name = "renderer_">Renderer de SDL</param>
	/// <param name = "size_">Tamaño de la imagen por pantalla</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	ImageButton(const char* imgButId, const std::string fileName, SDL_Renderer* renderer_, std::function<void(void)> funct,
		forge::Vector2 size_, forge::Vector2 pos_ = forge::Vector2::ZERO);

	/// <summary>
	/// Destructora del componente boton con imagen
	/// </summary>	
	~ImageButton();

	/// <summary>
	/// Actualizacion del boton con imagen
	/// </summary>
	virtual bool update();

	/// <summary>
	/// Actualiza la posicion
	/// </summary>	
	/// <param name = "pos_">Posicion</param>
	void setPosition(forge::Vector2 pos_) override;
};
#endif // !IMAGEBUTTON_H_

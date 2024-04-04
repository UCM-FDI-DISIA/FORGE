#pragma once

#ifndef IMAGEBUTTON_H_
#define IMAGEBUTTON_H_

#include "SDL_image.h"
#include "BaseButton.h"

class ImageButton : public BaseButton {
private:
	// Estados del botón
	enum ButtonState {
		IDLE, HOVER //, PRESSED
	};
	std::string idleFile;
	std::string hoverFile;

	// Vector de imagenes de estado
	std::vector<SDL_Texture*> images;

	// Posicion de renderizado
	forge::Vector2 realPos;

	// Marcador de tipo de feedback visual del boton
	bool imagesBool;

	bool createImage(std::string fileName, ButtonState state);

public:
	// Id de componente
	static const std::string id;

	/// <summary>
	/// Crea un botón con una imagen a partir de un archivo. Se aceptan varios tipos de imagen, entre ellos: PNG,
	/// JPG y SVG  
	/// </summary>	
	ImageButton();

	/// <summary>
	/// Destructora del componente boton con imagen
	/// </summary>	
	~ImageButton();

	/// <summary>
	/// Inicializa el ImageButton con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Actualizacion del boton con imagen
	/// </summary>
	virtual void update();
};
#endif // !IMAGEBUTTON_H_

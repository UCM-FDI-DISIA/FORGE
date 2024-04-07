//#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include "BaseButton.h"

struct ImFont;

class Button : public BaseButton {
private:
	// Texto del boton
	const char* text;

	// Color de los elementos del boton
	forge::Vector4 textColor;
	forge::Vector4 buttonColor;
	forge::Vector4 buttonHoverColor;
	forge::Vector4 buttonActiveColor;

	// Nombre de la fuente
	std::string fontName;
	// Fuente
	ImFont* font = nullptr;

public:
	// Id de componente
	static const std::string id;

	#pragma region Constructores
	/// <summary>
	/// Crea un boton. Por defecto se crea el texto en color
	/// blanco, con la primera fuente cargada por defecto y el fondo azul. Para cambiar las
	/// caracteristicas del boton utilizar metodos set.
	/// </summary>
	Button();
	~Button();
	#pragma endregion

	/// <summary>
	/// Inicializa el Button con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Actualizacion del boton
	/// </summary>
	virtual void update();

	/// <summary>
	/// Cambia el color del boton en los tres estados (idle, hover y active)
	/// </summary>	
	/// <param name = "color_">Color del boton</param>
	void setColor(forge::Vector4 color_);
	/// <summary>
	/// Cambia el color del boton
	/// </summary>	
	/// <param name = "color_">Color del boton</param>
	void setButtonColor(forge::Vector4 color_);
	/// <summary>
	/// Cambia el color del boton cuando se pasa por encima
	/// </summary>	
	/// <param name = "color_">Color del boton</param>
	void setButtonHoverColor(forge::Vector4 color_);
	/// <summary>
	/// Cambia el color del boton cuando se pulsa
	/// </summary>	
	/// <param name = "color_">Color del boton</param>
	void setButtonActiveColor(forge::Vector4 color_);

	/// <summary>
	/// Cambia la fuente del texto
	/// </summary>	
	/// <param name = "fontName_">Nombre de la fuente</param>
	void changeFont(std::string fontName_);
	/// <summary>
	/// Cambia la opacidad del boton
	/// </summary>	
	/// <param name = "op">Opacidad</param>
	void changeButtonOpacity(float op = 1.0f);
	/// <summary>
	/// Cambia el texto
	/// </summary>	
	/// <param name = "text_">Posicion</param>
	void changeText(const char* text_);	
};
#endif // !BUTTON_H_
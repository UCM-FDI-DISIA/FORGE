#pragma once
#ifndef BUTTON_H_
#define BUTTON_H_
#include "UIComponent.h"
class Button  : public UIComponent {
private:
 	static const std::string id;
	const char* text;
	forge::Vector4 textColor;
	forge::Vector4 buttonColor;
	forge::Vector4 buttonHoverColor;
	forge::Vector4 buttonActiveColor;
	std::string fontName;
	ImFont* font = nullptr;
	forge::Vector2 buttonSize;
	bool pressed;

public:
	#pragma region Constructores
	/// <summary>
	/// Crea un boton. Por defecto se crea el texto en color
	///  blanco, con la primera fuente cargada por defecto y el fondo azul. Para cambiar las
	/// caracteristicas del boton utilizar metodos set.
	/// </summary>	
	/// <param name = "buttonId">Nombre del boton</param>
	/// <param name = "buttonext">Texto del boton</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	Button(const char* buttonId, const char* buttonText, forge::Vector2 pos_ = forge::Vector2::ZERO);
	~Button();
	#pragma endregion
	/// <summary>
	/// Actualizacion del boton
	/// </summary>
	bool update();

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
	/// <summary>
	/// Devuelve true si el boton esta pulsado
	/// </summary>	
	bool isPressed();
};
#endif // !BUTTON_H_


#pragma once

#ifndef TEXT_H_
#define TEXT_H_

#include "UIComponent.h"

class Text  : public UIComponent {
private:
	static const std::string id;

protected:
	const char* text;

	forge::Vector4 color;
	forge::Vector4 bgColor;

	std::string fontName;
	ImFont* font = nullptr;

	forge::Vector2 size;

public:
	/// <summary>
	/// Crea un texto fijo. Se crea el texto en color
	///  blanco y con la primera fuente cargada por defecto. Para cambiar las
	/// caracteristicas del texto utilizar metodos set.
	/// </summary>	
	/// <param name = "textId">Identificador del texto (los identificadores de componetes UI NO PUEDEN COINCIDIR)</param>
	/// <param name = "text_">Texto a mostrar</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	Text(const char* textId, const char* text_, forge::Vector2 pos_ = forge::Vector2::ZERO);
	
	/// <summary>
	/// Destructora
	/// </summary>	
	~Text();

	/// <summary>
	/// Actualizacion del texto
	/// </summary>	
	virtual bool update();

	/// <summary>
	/// Cambia el color del texto
	/// </summary>	
	/// <param name = "color_">Color del texto</param>
	void setColor(forge::Vector4 color_);

	/// <summary>
	/// Cambia el tamano del "fondo" del texto
	/// </summary>	
	/// <param name = "size_">Tamano del fondo</param>
	void setSize(forge::Vector2 size_);

	/// <summary>
	/// Anade un fondo al texto del color y tamano dados
	/// </summary>	
	/// <param name = "color_">Color del fondo</param>
	/// <param name = "size_">Tamano del fondo</param>
	void setBackground(forge::Vector4 color_ = forge::Vector4({ 0.0, 0.0, 0.0, 1.0 }), forge::Vector2 size_ = forge::Vector2::ZERO);

	/// <summary>
	/// Quita el fondo
	/// </summary>	
	void removeBackground();
	
	/// <summary>
	/// Cambia la fuente
	/// </summary>	
	/// <param name = "fontName_">Nombre de la fuente</param>
	void changeFont(std::string fontName_);

	/// <summary>
	/// Cambia la opacidad del texto
	/// </summary>	
	/// <param name = "op">Opacidad</param>
	void changeTextOpacity(float op = 1.0f);
	/// <summary>
	/// Cambia la opacidad del fondo
	/// </summary>	
	/// <param name = "op">Opacidad</param>
	void changeBackgroundOpacity(float op = 1.0f);
	
	/// <summary>
	/// Cambia el texto
	/// </summary>	
	/// <param name = "text_">Posicion</param>
	void changeText(const char* text_);

	/// <summary>
	/// Devuelve el texto
	/// </summary>	
	const char* getText();
};
#endif // !TEXT_H_
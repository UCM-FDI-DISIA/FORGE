#pragma once

#ifndef TEXT_H_
#define TEXT_H_

#include "UIComponent.h"

struct ImFont;

class Text : public UIComponent {
protected:
	// Texto a mostrar
	const char* text;

	// Color de texto
	forge::Vector4 color;

	// Color de fondo
	forge::Vector4 bgColor;

	// Nombre de la fuente
	std::string fontName;

	// Fuente
	ImFont* font = nullptr;

public:
	// Id de componente
	static const std::string id;

	/// <summary>
	/// Crea un texto fijo. Se crea el texto en color
	///  blanco y con la primera fuente cargada por defecto. Para cambiar las
	/// caracteristicas del texto utilizar metodos set.
	/// </summary>
	Text();
	
	/// <summary>
	/// Destructora
	/// </summary>	
	~Text();

	/// <summary>
	/// Inicializa el Text con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Actualizacion del texto
	/// </summary>	
	virtual void update();

	/// <summary>
	/// Cambia el color del texto
	/// </summary>	
	/// <param name = "color_">Color del texto</param>
	void setColor(forge::Vector4 color_);

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
	/// <returns>El texto</returns>
	const char* getText();
};
#endif // !TEXT_H_
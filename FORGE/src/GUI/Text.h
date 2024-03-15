#pragma once
#ifndef TEXT_H_
#define TEXT_H_
#include <Component.h>
#include "Vector2.h"
#include "Vector4.h"
#include "imgui.h"
class GUI;
class Text /* : public Component*/ {
private:
	static const std::string id;
	const char* windowName;
	const char* text;
	// preguntar como hacer la conversion a ImVec
	forge::Vector2 pos;
	forge::Vector4 color;
	forge::Vector4 bgColor;
	std::string fontName;
	ImGuiWindowFlags window_flags = 0;
	ImFont* font = nullptr;
	forge::Vector2 size;
	GUI* gui;

public:
	/// <summary>
	/// Crea un texto fijo
	/// </summary>	
	/// <param name = "textId">Nombre del texto</param>
	/// <param name = "text_">Texto a mostrar</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	/// <param name = "color_">Color del texto</param>
	/// <param name = "fontName_">Nombre de la fuente en el mapa</param>
	Text(const char* textId, const char* text_, forge::Vector2 pos_ = forge::Vector2::ZERO,
		forge::Vector4 color_ = forge::Vector4({ 1.0, 1.0, 1.0, 1.0 }), std::string fontName_ = "");
	/// <summary>
	/// Actualizacion del texto
	/// </summary>	
	void update();
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
};
#endif // !TEXT_H_
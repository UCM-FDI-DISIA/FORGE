#pragma once
#include <Component.h>
#include "Vector2.h"
#include "Vector4.h"
#include "imgui.h"
class GUI;
class UIComponent /*: public Component*/ {
protected:
	const char* windowName;

	forge::Vector2 pos;

	ImGuiWindowFlags window_flags = 0;

	GUI* gui;

public:
	/// <summary>
	/// Contruye un componente de interfaz
	/// </summary>	
	/// <param name = "id">Nombre (identificador)</param>
	/// <param name = "pos_">Posicion</param>
	UIComponent(const char* id, forge::Vector2 pos_ = forge::Vector2::ZERO);
	/// <summary>
	/// Destructora
	/// </summary>	
	~UIComponent();

	/// <summary>
	/// Actualiza la posicion
	/// </summary>	
	/// <param name = "pos_">Posicion</param>
	void setPosition(forge::Vector2 pos_);
};


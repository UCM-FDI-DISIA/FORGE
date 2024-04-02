#pragma once
#include <Component.h>
#include "Vector2.h"
#include "Vector4.h"
#include "imgui.h"
#include "GUIManager.h"
class UIComponent /*: public Component*/ {
protected:
	// Identificador de ventana
	const char* windowName;

	// Posicion de renderizado
	forge::Vector2 pos;

	// Propiedades de la ventana (Flags)
	ImGuiWindowFlags window_flags = 0;

	// Referencia al GuiManager
	GUIManager* gui;

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
	virtual void setPosition(forge::Vector2 pos_);
};


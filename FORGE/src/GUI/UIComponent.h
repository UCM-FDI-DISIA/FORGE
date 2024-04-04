#pragma once

#ifndef UI_COMPONENT_H_
#define UI_COMPONENT_H_

#include <Component.h>
#include <Vector2.h>
#include <Vector4.h>
#include "RectTransform.h"
#include "GUIManager.h"

class UIComponent : public Component {
protected:
	// Identificador de ventana
	const char* windowName;

	// Propiedades de la ventana (Flags)
	ImGuiWindowFlags window_flags;

	// Referencia al GuiManager
	GUIManager* gui;

	// Referencia al transform
	RectTransform* transform;

	// Tamano del objeto
	forge::Vector2 size;

public:
	// Id de componente
	static const std::string id;

	#pragma region Constructores
	/// <summary>
	/// Contructora de un componente de interfaz
	/// </summary>	
	UIComponent();
	/// <summary>
	/// Destructora
	/// </summary>	
	virtual ~UIComponent();
	#pragma endregion

	/// <summary>
	/// Inicializa el UIComponent con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	bool initComponent(ComponentData* data) override;

	#pragma region Getters
	/// <summary>
	/// Devuelve el tamano de la imagen
	/// </summary>	
	forge::Vector2 getSize();
	#pragma endregion
};

#endif // !UI_COMPONENT_H_
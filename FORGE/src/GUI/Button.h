#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include <functional>
#include "UIComponent.h"

class Image;
class Input;

namespace forge {
	enum ButtonState { IDLE, HOVER };
}

class Button : public UIComponent {
private:
	// Control de estados
	forge::ButtonState state;

	// Texturas
	std::string idleTexture;
	std::string hoverTexture;

	// Puntero al componente de Imagen (obligatorio)
	Image* image;

	// Manager de input
	Input* input;

	// Control de pulsado
	bool pressed;

	// Callbacks
	static std::function<void(void)> mainFunc;
	std::function<void(void)> function;

	///// <summary>
	///// Cambia la imagen del boton por la del estado correspondiente
	///// </summary>
	void changeButtonImage();

public:
    // Id de componente
	static const FORGE_API_VAR std::string id;

	///// <summary>
	///// Contructora del componente Button
	///// </summary>	
	FORGE_API Button();

	///// <summary>
	///// Destructora
	///// </summary>	
	FORGE_API ~Button();

	///// <summary>
	///// Inicializa el Button con los parametros adecuados
	///// </summary>
	///// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	FORGE_API bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Update del UIComponent
	/// </summary>
	void update() override;

	/// <summary>
	/// Resetea la funcion principal de los botones, asignandola como nula
	/// </summary>	
	static void resetFunction();

	/// <summary>
	/// Llama a la funcion principal de los botones en caso de no ser nula, devolviendo si se ha ejecutado
	/// </summary>	
	/// <returns>Si habia una funcion asignada y se ha podido ejecutar</returns>
	static bool mainFunctionCall();

	#pragma region Getters
	/// <summary>
	/// Devuelve true si el boton esta pulsado
	/// </summary>
	/// <returns>True si el boton esta pulsado, false si no</returns>
	FORGE_API bool isPressed();
	#pragma endregion
};

#endif // !BUTTON_H_


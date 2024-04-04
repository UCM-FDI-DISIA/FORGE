//#pragma once

#ifndef BASE_BUTTON_H_
#define BASE_BUTTON_H_

#include "UIComponent.h"
#include <functional>

class BaseButton : public UIComponent {
private:
	// Id de componente
	static const std::string id;

protected:
	// Identificador del boton(debe ser único para cada uno)
	const char* buttonId;

	// Control de pulsado
	bool pressed;

	// Callbacks
	static std::function<void(void)> mainFunc;
	std::function<void(void)> function;

public:
	#pragma region Constructores
	BaseButton();
	~BaseButton();
	#pragma endregion

	/// <summary>
	/// Inicializa el BaseButton con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	bool initComponent(ComponentData* data) override;

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
	bool isPressed();
	#pragma endregion
};

#endif // !BASE_BUTTON_H_
#pragma once

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

	// Tamano del boton
	forge::Vector2 buttonSize;

	// Control de pulsado
	bool pressed;

	// Callbacks
	static std::function<void(void)> mainFunc;
	std::function<void(void)> function;

public:
	BaseButton(const char* bId, std::function<void(void)> funct, forge::Vector2 bSize, forge::Vector2 bPos);
	~BaseButton();

	/// <summary>
	/// Actualizacion del boton
	/// </summary>
	virtual bool update() = 0;

	/// <summary>
	/// Cambia el tamano del boton
	/// </summary>	
	/// <param name = "size">Nuevo tamano</param>
	void setSize(forge::Vector2 size);

	/// <summary>
	/// Devuelve true si el boton esta pulsado
	/// </summary>
	/// <returns>True si el boton esta pulsado, false si no</returns>
	bool isPressed();

	/// <summary>
	/// Resetea la funcion principal de los botones, asignandola como nula
	/// </summary>	
	static void resetFunction();

	/// <summary>
	/// Llama a la funcion principal de los botones en caso de no ser nula, devolviendo si se ha ejecutado
	/// </summary>	
	/// <returns>Si habia una funcion asignada y se ha podido ejecutar</returns>
	static bool mainFunctionCall();
};

#endif // !BASE_BUTTON_H_
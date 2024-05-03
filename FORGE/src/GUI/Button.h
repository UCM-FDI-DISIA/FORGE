#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include <functional>
#include "Image.h"

class Input; 
template <typename T>
class ForgeFunction;

namespace forge {
	enum ButtonState { OUT_STATE, HOVER_STATE, CLICKED_STATE };
}

class Button : public Image {
private:
	// Control de estados
	forge::ButtonState state;
	forge::ButtonState newState;

	// Texturas
	std::string outTexture;
	std::string hoverTexture;
	std::string clickedTexture;

	// Manager de input
	Input* input;

	// Control de pulsado
	bool clicked;

	// Callbacks
	static std::function<void(void)> mainFunc;
	ForgeFunction<void>* onOver;
	ForgeFunction<void>* onClick;
	ForgeFunction<void>* onRelease;

	///// <summary>
	///// Cambia la imagen del boton por la del estado correspondiente
	///// </summary>
	void changeButtonImage();

	/// <summary>
	/// Comprueba la posicion del raton para actualizar el estado
	/// </summary>
	void checkMousePosition();

	void checkCallbacks();

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
	///// <param name="data">Parametros necesarios para la iniciacion del componente</param>
	FORGE_API bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Activa el componente (llama a crear la imagen)
	/// </summary>	
	virtual FORGE_API void onEnabled();

	/// <summary>
	/// Desactiva el componente (llama a destruir la imagen)
	/// </summary>	
	virtual FORGE_API void onDisabled();

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


#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include <functional>
#include "Image.h"

class Input; 
template <typename T>
class ForgeFunction;
class Invoker;

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
	Input& input;

	// Control de pulsado
	bool clicked;

	// Callbacks
	ForgeFunction<void>* onOver;
	ForgeFunction<void>* onClick;
	ForgeFunction<void>* onRelease;
	Invoker* onOverInvoker;
	Invoker* onClickInvoker;
	Invoker* onReleaseInvoker;

	///// <summary>
	///// Cambia la imagen del boton por la del estado correspondiente
	///// </summary>
	void changeButtonImage();

	/// <summary>
	/// Comprueba la posicion del raton para actualizar el estado
	/// </summary>
	void checkMousePosition();

	/// <summary>
	/// Comprueba el estado del boton y llama a los callbacks correspondientes si es necesario
	/// </summary>
	void checkCallbacks();

	/// <summary>
	/// Inicializa el invocadores de un callback
	/// </summary>
	/// <param name="data">ComponentData del que se esta leyendo la informacion</param>
	/// <param name="invoker">Invocador que se quiere inicializar</param>
	/// <param name="name">Nombre del invocador en Lua</param>
	/// <returns></returns>
	bool initInvoker(ComponentData* data, Invoker*& invoker, std::string const& name);

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
	FORGE_API void onEnabled() override;

	/// <summary>
	/// Desactiva el componente (llama a destruir la imagen)
	/// </summary>	
	FORGE_API void onDisabled() override;

	/// <summary>
	/// Update del UIComponent
	/// </summary>
	FORGE_API void update() override;

	#pragma region Getters
	/// <summary>
	/// Devuelve true si el boton esta pulsado
	/// </summary>
	/// <returns>True si el boton esta pulsado, false si no</returns>
	FORGE_API bool isPressed() const;
	#pragma endregion
};

#endif // !BUTTON_H_


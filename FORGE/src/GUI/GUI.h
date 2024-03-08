#pragma once

#include <memory>
#include <iostream>
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h> 
//#include "Vector2.h"

class GUI {
private:
	static std::unique_ptr<GUI> instance;
public:
	struct Vector4 { float x, y, z, w; };
	static GUI* getInstance();
	GUI();
	~GUI();

	/// <summary>
	/// Crea un texto fijo
	/// </summary>	
	/// <param name = "text"> 
	/// Texto a mostrar
	/// </param>
	/// <param name = "pos"> 
	/// Posicion de renderizado
	/// </param>
	/// <param name = "fontSize"> 
	/// Tamano de texto
	/// </param>
	/// <param name = "color"> 
	/// Color del texto
	/// </param>
	void createText(const char* text/*, forge::Vector2 pos = forge::Vector2::ZERO*/, float fontSize = 1, Vector4 color = Vector4({ 1.0, 1.0, 1.0, 1.0 }));

};
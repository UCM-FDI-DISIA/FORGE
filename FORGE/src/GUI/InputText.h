#pragma once

#ifndef INPUTTEXT_H_
#define INPUTTEXT_H_

#include "Text.h"

class InputText : public Text {
private:
	// Id de componente
	static const std::string id;

	// Buffer del texto a escribir
	char textToWrite[64];

	// Texto que se quiere modificar a la vez
	Text* textToChange;

public:
	/// <summary>
	/// Crea un texto fijo que se puede modificar. Se crea el texto en color
	///  blanco y con la primera fuente cargada por defecto. Para cambiar las
	/// caracteristicas del texto utilizar metodos set.
	/// </summary>	
	/// <param name = "textId">Identificador del texto con input (los identificadores de componetes UI NO PUEDEN COINCIDIR)</param>
	/// <param name = "text_">Texto a mostrar "por debajo" (Recomendacion:"Introduce texto")</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	InputText(const char* textId, const char* text_, forge::Vector2 pos_ = forge::Vector2::ZERO);

	/// <summary>
	/// Crea un texto fijo que se puede modificar y cambia otro texto (textToChange_). Se crea el texto en color
	///  blanco y con la primera fuente cargada por defecto. Para cambiar las
	/// caracteristicas del texto utilizar metodos set.
	/// </summary>	
	/// <param name = "textId">Identificador del texto con input (los identificadores de componetes UI NO PUEDEN COINCIDIR)</param>
	/// <param name = "text_">Texto a mostrar "por debajo" (Recomendacion:"Introduce texto")</param>
	/// <param name = "textToChange_">Texto que se va a modificar a la vez que este</param>
	/// <param name = "pos_">Posicion de renderizado</param>
	InputText(const char* textId, const char* text_, Text* textToChange_, forge::Vector2 pos_ = forge::Vector2::ZERO);

	// <summary>
	/// Crea un texto fijo. Por defecto se crea el texto en color
	///  blanco y con la primera fuente cargada por defecto. Para cambiar las
	/// caracteristicas del texto utilizar metodos set.
	/// </summary>	
	~InputText();

	/// <summary>
	/// Actualizacion del texto
	/// </summary>	
	bool update() override;
};
#endif // !INPUTTEXT_H_


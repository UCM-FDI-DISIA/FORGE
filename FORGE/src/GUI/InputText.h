#pragma once

#ifndef INPUTTEXT_H_
#define INPUTTEXT_H_

#include "Text.h"

class InputText : public Text {
private:
	// Buffer del texto a escribir
	char textToWrite[64];

	// Texto que se quiere modificar a la vez
	Text* textToChange;

public:
	// Id de componente
	static const std::string id;

	/// <summary>
	/// Crea un texto fijo que se puede modificar y cambia otro texto (textToChange_). Se crea el texto en color
	///  blanco y con la primera fuente cargada por defecto. Para cambiar las
	/// caracteristicas del texto utilizar metodos set.
	/// </summary>
	InputText();

	// <summary>
	/// Crea un texto fijo. Por defecto se crea el texto en color
	///  blanco y con la primera fuente cargada por defecto. Para cambiar las
	/// caracteristicas del texto utilizar metodos set.
	/// </summary>	
	~InputText();

	/// <summary>
	/// Inicializa el InputText con los parametros adecuados
	/// </summary>
	/// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Actualizacion del texto
	/// </summary>	
	void update() override;
};
#endif // !INPUTTEXT_H_


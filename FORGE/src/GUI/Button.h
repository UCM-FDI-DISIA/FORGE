#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include "UIComponent.h"
class Button :
    public UIComponent
{
private:
public:
    // Id de componente
	static const FORGE_API_VAR std::string id;

	///// <summary>
	///// Contructora del componente boton
	///// </summary>	
	//FORGE_API Button();

	///// <summary>
	///// Destructora
	///// </summary>	
	//FORGE_API ~Button();

	///// <summary>
	///// Inicializa el UIComponent con los parametros adecuados
	///// </summary>
	///// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
	//FORGE_API bool initComponent(ComponentData* data) override;
};

#endif // !BUTTON_H_


#pragma once

#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_

#include "UIComponent.h"

namespace Ogre {
	class Image;
};

namespace forge {
	// La barra crece...
	enum GrowthMode {
		LEFT_TO_RIGHT,	// De derecha a izquierda
		RIGHT_TO_LEFT,	// De izquierda a derecha
		UP_TO_DOWN,		// De abajo a arriba
		DOWN_TO_UP		// De arriba a abajo
	};
}

class ProgressBar : public UIComponent {
private:
	// Textura de fondo
	std::string frontTexture;
	std::string backTexture;

	Ogre::Image* frontImage;
	Ogre::Image* backImage;

	// Valor en porcentaje (0.0 al 1.0)
	float value;

	// Crecimiento de la barra
	std::string readAux;
	forge::GrowthMode growth;
	
	// Contenedores del elemento de ogre
	Ogre::OverlayContainer* frontPanel;
	Ogre::Overlay* frontOverlay;

	/// <summary>
	/// Cambia las dimensiones en X segun el valor
	/// </summary>	
	void adjust();

	/// <summary>
	/// Crea los elementos de la barra de progreso
	/// </summary>	
	void createProgressBar();

	/// <summary>
	/// Destruye los elementos de la barra de progreso
	/// </summary>	
	void destroyProgressBar();

public:
	// Id de componente
	static const FORGE_API_VAR std::string id;

	/// <summary>
	/// Constructora del componente de barra de progreso
	/// </summary>	
	FORGE_API ProgressBar();

	/// <summary>
	/// Destructora del componente de barra de progreso
	/// </summary>	
	FORGE_API ~ProgressBar();

	/// <summary>
	/// Inicializa la Image con los parametros adecuados
	/// </summary>
	/// <param name="data">Parametros necesarios para la iniciacion del componente</param>
	FORGE_API bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Ajusta el UIComponent al nuevo ajuste de la ventana
	/// </summary>
	FORGE_API void resize(forge::Vector2 const& prev, forge::Vector2 const& updated) override;

	/// <summary>
	/// Activa el componente (llama a crear la imagen)
	/// </summary>	
	FORGE_API void onEnabled() override;

	/// <summary>
	/// Desactiva el componente (llama a destruir la imagen)
	/// </summary>	
	FORGE_API void onDisabled() override;

	#pragma region Getters
	/// <summary>
	/// Devuelve la textura trasera
	/// </summary>	
	FORGE_API std::string getBackTexture();

	/// <summary>
	/// Devuelve la textura frontal
	/// </summary>	
	FORGE_API std::string getFrontTexture();
	#pragma endregion

	#pragma region Setters
	/// <summary>
	/// Setea el valor de la barra
	/// </summary>
	/// <param name="v">Nuevo valor</param>
	FORGE_API void setValue(float v);

	/// <summary>
	/// Decrece el valor de la barra
	/// </summary>
	/// <param name="v">Valor a decrecer</param>
	FORGE_API void decrease(float v);
	
	/// <summary>
	/// Incrementa el valor de la barra
	/// </summary>
	/// <param name="v">Valor a aumentar</param>
	FORGE_API void increase(float v);
	#pragma endregion


};

#endif // !PROGRESSBAR_H_
#pragma once

#ifndef TEXT_H_
#define TEXT_H_

#include "UIComponent.h"

namespace Ogre {
    class Font;
	class TextAreaOverlayElement;
}

namespace forge {
	enum Alignment {CENTER, RIGHT, LEFT};
}

class Text : public UIComponent {
private:
    // Texto a mostrar
    std::string text;

    // Color de texto
    forge::Vector4 color;

    // Color de fondo
    forge::Vector4 bgColor;

    // Nombre de la fuente
    std::string fontName;

	// Altura de la fuente
	int fontHeight;

	// Elemento de overlay para el texto
	Ogre::TextAreaOverlayElement* textAreaOverlay;

	/// <summary>
	/// Crea el texto con su Panel y su Overlay
	/// </summary>	
	void createText();

	/// <summary>
	/// Destruye el texto con su Panel y su Overlay
	/// </summary>	
	void destroyText();

	/// <summary>
	/// Calcula la longitud del componente de texto
	/// </summary>
	/// <returns>La longitud calculada</returns>
	float calculateTextWidth();

	/// <summary>
	/// Calcula la esquina superior izquierda del texto
	/// </summary>
	/// <returns>Un vector correspondiente</returns>
	forge::Vector2 getUpperLeftPoint();

public:
    static const FORGE_API_VAR std::string id;

    /// <summary>
    /// Contructora del componente texto
    /// </summary>	
    FORGE_API Text();

    /// <summary>
    /// Destructora
    /// </summary>	
    FORGE_API ~Text();

    /// <summary>
    /// Inicializa el UIComponent con los parametros adecuados
    /// </summary>
    /// <param name="data"> Parametros necesarios para la iniciacion del componente</param>
    FORGE_API bool initComponent(ComponentData* data) override;

	/// <summary>
	/// Activa el componente (llama a crear el texto)
	/// </summary>	
    virtual FORGE_API void onEnabled();

	/// <summary>
	/// Desactiva el componente (llama a destruir el texto)
	/// </summary>	
    virtual FORGE_API void onDisabled();

	/// <summary>
	/// Cambia la opacidad del fondo
	/// </summary>	
	/// <param name = "op">Opacidad</param>
	FORGE_API void changeBackgroundOpacity(float op = 1.0f);

	#pragma region Getters
	/// <summary>
	/// Devuelve el texto
	/// </summary>	
	/// <returns>El texto</returns>
	FORGE_API std::string getText() const;

	/// <summary>
	/// Devuelve el color del texto
	/// </summary>
	/// <returns>El vector 4 que representa el color</returns>
	FORGE_API forge::Vector4 getColor() const;
	#pragma endregion

	#pragma region Setters
	/// <summary>
	/// Cambiar la posicion del texto
	/// </summary>
	/// <param name="newPosition">La nueva posicion del texto</param>
	FORGE_API void setPosition(forge::Vector2 const& newPosition);

	/// <summary>
    /// Asigna un tamaño
    /// </summary>	
    /// <param name="fSize">Altura a asignar</param>
	FORGE_API void setHeight(int fHeight);

	/// <summary>
	/// Cambia la fuente
	/// </summary>	
	/// <param name = "fontName_">Nombre de la fuente</param>
	FORGE_API void setFont(std::string const& fontName_);

	/// <summary>
	/// Cambia el texto
	/// </summary>	
	/// <param name = "text_">Texto nuevo</param>
	FORGE_API void setText(std::string const& text_);

	/// <summary>
	/// Cambia el color del texto
	/// </summary>
	/// <param name="c">El nuevo color en formato Vector4</param>
	FORGE_API void setColor(forge::Vector4 c);

	/// <summary>
	/// Cambia la opacidad del texto
	/// </summary>	
	/// <param name = "op">Opacidad</param>
	FORGE_API void setTextOpacity(float op = 1.0f);

	/// <summary>
	/// Coloca el texto con distinta alineacion
	/// </summary>
	/// <param name="a">La nueva alineacion del texto</param>
	FORGE_API void setTextAligment(forge::Alignment a);
	#pragma endregion
};

#endif // !TEXT_H_
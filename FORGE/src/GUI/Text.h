#pragma once

#ifndef TEXT_H_
#define TEXT_H_

#include "UIComponent.h"

namespace Ogre {
    class Font;
	class TextAreaOverlayElement;
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

    // La fuente
    Ogre::Font* font;

	// Elemento de overlay para el texto
	Ogre::TextAreaOverlayElement* textAreaOverlay;

public:
    static const FORGE_API_VAR std::string id;

    /// <summary>
    /// Contructora de un componente de interfaz
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


    virtual FORGE_API void onEnabled();


    virtual FORGE_API void onDisabled();

	/// <summary>
	/// Actualizacion del texto
	/// </summary>	
	//virtual void update();

	/// <summary>
	/// Cambia el color del texto
	/// </summary>	
	/// <param name = "color_">Color del texto</param>
	void setColor(forge::Vector4 color_);

	/// <summary>
	/// Anade un fondo al texto del color y tamano dados
	/// </summary>	
	/// <param name = "color_">Color del fondo</param>
	/// <param name = "size_">Tamano del fondo</param>
	void setBackground(forge::Vector4 color_ = forge::Vector4({ 0.0, 0.0, 0.0, 1.0 }), forge::Vector2 size_ = forge::Vector2::ZERO);

	/// <summary>
	/// Quita el fondo
	/// </summary>	
	void removeBackground();

	/// <summary>
	/// Cambia la fuente
	/// </summary>	
	/// <param name = "fontName_">Nombre de la fuente</param>
	void changeFont(std::string const& fontName_);

	/// <summary>
	/// Cambia la opacidad del texto
	/// </summary>	
	/// <param name = "op">Opacidad</param>
	void changeTextOpacity(float op = 1.0f);
	/// <summary>
	/// Cambia la opacidad del fondo
	/// </summary>	
	/// <param name = "op">Opacidad</param>
	void changeBackgroundOpacity(float op = 1.0f);

	/// <summary>
	/// Cambia el texto
	/// </summary>	
	/// <param name = "text_">Texto nuevo</param>
	void changeText(std::string const& text_);

	/// <summary>
	/// Devuelve el texto
	/// </summary>	
	/// <returns>El texto</returns>
	std::string getText() const;
};

#endif // !TEXT_H_
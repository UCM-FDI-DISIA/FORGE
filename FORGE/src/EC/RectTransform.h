#pragma once
#ifndef RECTTRANSFORM_H_
#define RECTTRANSFORM_H_

#include "Component.h"
#include "Vector2.h"

class RectTransform : public Component {
	friend Entity;
private:
	forge::Vector2 position;
	forge::Vector2 scale;

	bool needsUpdate;

public:
	static const FORGE_API_VAR std::string id;

	FORGE_API RectTransform();

	#pragma region setters
	/// <summary>
	/// Establece la posicion del RectTransform
	/// </summary>
	/// <param name="newPos">Nueva posicion del RectTransform</param>
	FORGE_API void setPosition(forge::Vector2 const& newPos);
	/// <summary>
	/// Mueve la posicion en la cantidad indicada
	/// </summary>
	/// <param name="offset">Cantidad de desplazamiento a aplicar</param>
	FORGE_API void movePosition(forge::Vector2 const& offset);
	/// <summary>
	/// Establece la posicion en el eje x
	/// </summary>
	/// <param name="newX">Nueva posicion en el eje x</param>
	FORGE_API void setPositionX(float newX);
	/// <summary>
	/// Establece la posicion en el eje y
	/// </summary>
	/// <param name="newY">Nueva posicion en el eje y</param>
	FORGE_API void setPositionY(float newY);

	/// <summary>
	/// Establece la escala del RectTransform
	/// </summary>
	/// <param name="newScale">Nueva escala del RectTransform</param>
	FORGE_API void setScale(forge::Vector2 const& newScale);
	/// <summary>
	/// Establece los dos valores de la escala del RectTransform
	/// </summary>
	/// <param name="newScale">Nueva escala del RectTransform</param>
	FORGE_API void setScale(float scale);
	/// <summary>
	/// Escala el RectTransform.
	/// </summary>
	/// <param name="newScale">Escala a aplicar al RectTransform</param>
	FORGE_API void doScale(forge::Vector2 const& newScale);
	/// <summary>
	/// Escala en los dos valores el RectTransform.
	/// </summary>
	/// <param name="newScale">Escala a aplicar al RectTransform</param>
	FORGE_API void doScale(float scale);
	/// <summary>
	/// Establece si requiere actualizarse la instancia del RectTransform
	/// </summary>
	/// <param name="needed">True si lo necesita, false si no lo necesita</param>
	FORGE_API void setNeedsUpdate(bool needed);

	#pragma endregion //setters

	#pragma region getters
	/// <returns>Posicion local</returns>
	FORGE_API forge::Vector2 const& getPosition() const;
	/// <returns>Escala local</returns>
	FORGE_API forge::Vector2 const& getScale() const;
	///<returns>Se ha actualizado el RectTransform</returns>
	FORGE_API bool getNeedsUpdate() const;
	#pragma endregion //getters

};

#endif // !RECTTRANSFORM_H_
#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Component.h"
#include "Vector3.h"
#include "Quaternion.h"

class Transform : public Component {
	friend Entity;
private:

	forge::Vector3 position;
	forge::Quaternion rotation;
	forge::Vector3 scale;

	Transform* parent;

	/// <summary>
	/// Establece el Transform de la Entity padre.
	/// </summary>
	/// <param name="newParent">Puntero al Transform de la nueva Entity padre.</param>
	void setParent(Transform* newParent);
public:
	Transform();

#pragma region setters
	/// <summary>
	/// Establece la rotacion al Quaternion pasado.
	/// </summary>
	/// <param name="newRot">Nueva rotacion del Transform.</param>
	void setRotation(forge::Quaternion const& newRot);
	/// <summary>
	/// Establece la rotacion al Vector3 pasado interpretado como angulos de Euler.
	/// </summary>
	/// <param name="newRot">Nueva rotacion del Transform.</param>
	void setRotation(forge::Vector3 const& newRot);
	/// <summary>
	/// Rota el transform en el eje x.
	/// </summary>
	/// <param name="xRot">Rotacion a aplicar en el eje x.</param>
	void rotateX(float xRot);
	/// <summary>
	/// Rota el transform en el eje y.
	/// </summary>
	/// <param name="yRot">Rotacion a aplicar en el eje y.</param>
	void rotateY(float yRot);
	/// <summary>
	/// Rota el transform en el eje z.
	/// </summary>
	/// <param name="zRot">Rotacion a aplicar en el eje z.</param>
	void rotateZ(float zRot);

	/// <summary>
	/// Establece la posicion del Transform.
	/// </summary>
	/// <param name="newPos">Nueva posicion del Transform.</param>
	void setPosition(forge::Vector3 const& newPos);
	/// <summary>
	/// Mueve la posicion en la cantidad indicada.
	/// </summary>
	/// <param name="offset">Cantidad de desplazamiento a aplicar.</param>
	void movePosition(forge::Vector3 const& offset);
	/// <summary>
	/// Establece la posicion en el eje x.
	/// </summary>
	/// <param name="newX">Nueva posicion en el eje x.</param>
	void setPositionX(float newX);
	/// <summary>
	/// Establece la posicion en el eje y.
	/// </summary>
	/// <param name="newY">Nueva posicion en el eje y.</param>
	void setPositionY(float newY);
	/// <summary>
	/// Establece la posicion en el eje z.
	/// </summary>
	/// <param name="newZ">Nueva posicion en el eje z.</param>
	void setPositionZ(float newZ);

	/// <summary>
	/// Establece la escala del Transform.
	/// </summary>
	/// <param name="newScale">Nueva escala del Transform.</param>
	void setScale(forge::Vector3 const& newScale);
	/// <summary>
	/// Establece los tres valores de la escala del Transform.
	/// </summary>
	/// <param name="newScale">Nueva escala del Transform.</param>
	void setScale(float scale);
	/// <summary>
	/// Escala el Transform.
	/// </summary>
	/// <param name="newScale">Escala a aplicar al Transform.</param>
	void doScale(forge::Vector3 const& newScale);
	/// <summary>
	/// Escala en los tres valores el Transform.
	/// </summary>
	/// <param name="newScale">Escala a aplicar al Transform.</param>
	void doScale(float scale);

#pragma endregion //setters
#pragma region getters
	/// <returns>Rotacion local.</returns>
	forge::Quaternion const& getRotation() const;
	/// <returns>Rotacion global.</returns>
	forge::Quaternion getGlobalRotation() const;
	/// <returns>Rotacion local en angulos de Euler.</returns>
	forge::Vector3 const&& getRotationEuler() const;
	/// <returns>Rotacion global en angulos de Euler.</returns>
	forge::Vector3 const&& getGlobalRotationEuler() const;
	/// <returns>Posicion local.</returns>
	forge::Vector3 const& getPosition() const;
	/// <returns>Posicion global.</returns>
	forge::Vector3 getGlobalPosition() const;
	/// <returns>Escala local.</returns>
	forge::Vector3 const& getScale() const;
	/// <returns>Escala global.</returns>
	forge::Vector3 getGlobalScale() const;
#pragma endregion //getters
};

#endif // !TRANSFORM_H_
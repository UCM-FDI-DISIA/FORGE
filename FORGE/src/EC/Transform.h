#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Component.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "ForgeExport.h"

class Transform : public Component {
	friend Entity;
private:

	forge::Vector3 position;
	forge::Quaternion rotation;
	forge::Vector3 scale;

	bool needsUpdate;

	Transform* parent;

	/// <summary>
	/// Establece el Transform de la Entity padre.
	/// </summary>
	/// <param name="newParent">Puntero al Transform de la nueva Entity padre.</param>
	void setParent(Transform* newParent);
public:
	static  const FORGE_API_VAR std::string id;

	FORGE_API Transform();
	FORGE_API bool initComponent(ComponentData* data);
	/// <summary>
	/// Establece que el Tranform ha sido actualizado
	/// </summary>
	FORGE_API void onEnabled() override;

	#pragma region setters
	/// <summary>
	/// Establece la rotacion al Quaternion pasado.
	/// </summary>
	/// <param name="newRot">Nueva rotacion del Transform.</param>
	FORGE_API void setRotation(forge::Quaternion const& newRot);
	/// <summary>
	/// Establece la rotacion al Vector3 pasado interpretado como angulos de Euler.
	/// </summary>
	/// <param name="newRot">Nueva rotacion del Transform.</param>
	FORGE_API void setRotation(forge::Vector3 const& newRot);
	/// <summary>
	/// Rota el transform en el eje x (recibe el angulo en grados)
	/// </summary>
	/// <param name="xRot">Rotacion a aplicar en el eje x.</param>
	FORGE_API void rotateX(float xRot);
	/// <summary>
	/// Rota el transform en el eje y (recibe el angulo en grados)
	/// </summary>
	/// <param name="yRot">Rotacion a aplicar en el eje y.</param>
	FORGE_API void rotateY(float yRot);
	/// <summary>
	/// Rota el transform en el eje z (recibe el angulo en grados)
	/// </summary>
	/// <param name="zRot">Rotacion a aplicar en el eje z.</param>
	FORGE_API void rotateZ(float zRot);
	/// <summary>
	/// Rota el transform en el eje x (recibe el angulo en radianes)
	/// </summary>
	/// <param name="xRot">Rotacion a aplicar en el eje x.</param>
	FORGE_API void rotateXRad(float xRot);
	/// <summary>
	/// Rota el transform en el eje y (recibe el angulo en radianes)
	/// </summary>
	/// <param name="yRot">Rotacion a aplicar en el eje y.</param>
	FORGE_API void rotateYRad(float yRot);
	/// <summary>
	/// Rota el transform en el eje z (recibe el angulo en radianes)
	/// </summary>
	/// <param name="zRot">Rotacion a aplicar en el eje z.</param>
	FORGE_API void rotateZRad(float zRot);

	/// <summary>
	/// Establece la posicion del Transform.
	/// </summary>
	/// <param name="newPos">Nueva posicion del Transform.</param>
	FORGE_API void setPosition(forge::Vector3 const& newPos);
	/// <summary>
	/// Mueve la posicion en la cantidad indicada.
	/// </summary>
	/// <param name="offset">Cantidad de desplazamiento a aplicar.</param>
	FORGE_API void movePosition(forge::Vector3 const& offset);
	/// <summary>
	/// Establece la posicion en el eje x.
	/// </summary>
	/// <param name="newX">Nueva posicion en el eje x.</param>
	FORGE_API void setPositionX(float newX);
	/// <summary>
	/// Establece la posicion en el eje y.
	/// </summary>
	/// <param name="newY">Nueva posicion en el eje y.</param>
	FORGE_API void setPositionY(float newY);
	/// <summary>
	/// Establece la posicion en el eje z.
	/// </summary>
	/// <param name="newZ">Nueva posicion en el eje z.</param>
	FORGE_API void setPositionZ(float newZ);

	/// <summary>
	/// Establece la escala del Transform.
	/// </summary>
	/// <param name="newScale">Nueva escala del Transform.</param>
	FORGE_API void setScale(forge::Vector3 const& newScale);
	/// <summary>
	/// Establece los tres valores de la escala del Transform.
	/// </summary>
	/// <param name="newScale">Nueva escala del Transform.</param>
	FORGE_API void setScale(float scale);
	/// <summary>
	/// Escala el Transform.
	/// </summary>
	/// <param name="newScale">Escala a aplicar al Transform.</param>
	FORGE_API void doScale(forge::Vector3 const& newScale);
	/// <summary>
	/// Escala en los tres valores el Transform.
	/// </summary>
	/// <param name="newScale">Escala a aplicar al Transform.</param>
	FORGE_API void doScale(float scale);
	/// <summary>
	/// Establece si requiere actualizarse la instancia del transform
	/// </summary>
	/// <param name="needed">True si lo necesita, falase sita no lo necesita.</param>
	FORGE_API void setNeedsUpdate(bool needed);
	/// <summary>
	/// Establece si requiere actualizarse la instancia de los hijos del transform
	/// </summary>
	/// <param name="needed">True si lo necesita, falase sita no lo necesita</param>
	FORGE_API void setChildNeedsUpdate(bool needed);

	#pragma endregion //setters
	#pragma region getters
	/// <returns>Rotacion local.</returns>
	FORGE_API forge::Quaternion const& getRotation() const;
	/// <returns>Rotacion global.</returns>
	FORGE_API forge::Quaternion getGlobalRotation() const;
	/// <returns>Rotacion local en angulos de Euler.</returns>
	FORGE_API forge::Vector3 getRotationEuler() const;
	/// <returns>Rotacion global en angulos de Euler.</returns>
	FORGE_API forge::Vector3 getGlobalRotationEuler() const;
	/// <returns>Posicion local.</returns>
	FORGE_API forge::Vector3 const& getPosition() const;
	/// <returns>Posicion global.</returns>
	FORGE_API forge::Vector3 getGlobalPosition() const;
	/// <returns>Escala local.</returns>
	FORGE_API forge::Vector3 const& getScale() const;
	/// <returns>Escala global.</returns>
	FORGE_API forge::Vector3 getGlobalScale() const;
	///<returns>Se ha actualizado el transform.</returns>
	FORGE_API bool getNeedsUpdate() const;
	/// <returns>Vector forward actual.</returns>
	FORGE_API forge::Vector3 getForward() const;
	/// <returns>Vector up actual.</returns>
	FORGE_API forge::Vector3 getUp() const;
	/// <returns>Vector right actual.</returns>
	FORGE_API forge::Vector3 getRight() const;
	#pragma endregion //getters
};

#endif // !TRANSFORM_H_
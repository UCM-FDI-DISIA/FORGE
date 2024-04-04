#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include "Component.h"
#include <string>
#include "Vector3.h"

class RenderManager;
namespace Ogre {
    class Camera;
}

class Camera : public Component {
private:
    float nearClipDistance;
    bool autoAspectRatio;
    forge::Vector3 backgroundColor;

    Ogre::Camera* ogreCamera;
    RenderManager* renderManager; 
public:
	static const std::string id;

    /// <summary>
    /// Crea Camera con valores por defecto
    /// </summary>
    Camera();
    /// <summary>
    /// Destruye la camara de Ogre asociada a este Camera
    /// </summary>
    ~Camera();

    /// <summary>
    /// Obtiene la referencia al singleton del RenderManager y la utiliza para
    /// crear una camara de Ogre que guarda en ogreCamera
    /// </summary>
    /// <param name="data"></param>
    bool initComponent(ComponentData* data) override;
    /// <summary>
    /// Crea una camara de Ogre que guarda en ogreCamera
    /// </summary>
    void onEnabled() override;
    /// <summary>
    /// Destruye la camara de Ogre asociada a este Camera
    /// </summary>
    void onDisabled() override;

	#pragma region setters
    /// <summary>
    /// Establece la distancia a la que se encuentra el plano de recorte cercano
    /// </summary>
    /// <param name="newNearClipDistance">Nueva distancia a la que se encuentra el plano de recorte cercano</param>
    void setNearClipDistance(float newNearClipDistance);
    /// <summary>
    /// Establece si la relacion de aspecto es automatica o no
    /// </summary>
    /// <param name="newAutoAspectRatio">Nuevo estado de la relacion de aspecto es automatica</param>
    void setAutoAspectRatio(bool newAutoAspectRatio);
    /// <summary>
    /// Establece el color de fondo
    /// </summary>
    /// <param name="newbackgroundColor">Nuevos valores RGB del fondo</param>
    void setBackgroundColor(forge::Vector3 newbackgroundColor);
	#pragma endregion

	#pragma region getters
    /// <summary>
    /// Devuelve la distancia a la que se encuentra el plano de recorte cercano
    /// </summary>
    /// <returns>Distancia a la que se encuentra el plano de recorte cercano</returns>
    const float& getNearClipDistance() const;
    /// <summary>
    /// Devuelve si la relacion de aspecto es automatica o no
    /// </summary>
    /// <returns>El estado de la relacion de aspecto automatica</returns>
    const bool& getAutoAspectRatio() const;
    /// <summary>
    /// Devuelve el color del fondo
    /// </summary>
    /// <returns>Un Vector3 con los valores RGB del fondo</returns>
    const forge::Vector3& getBackgroundColor() const;
	#pragma endregion
};

#endif // !CAMERA_H_
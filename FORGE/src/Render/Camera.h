#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include "Component.h"
#include <string>
#include "Vector3.h"
#include "ForgeExport.h"

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
    static const FORGE_API_VAR std::string id;

    /// <summary>
    /// Crea Camera con valores por defecto
    /// </summary>
    FORGE_API Camera();
    /// <summary>
    /// Destruye la camara de Ogre asociada a este Camera
    /// </summary>
    FORGE_API ~Camera();

    /// <summary>
    /// Obtiene la referencia al singleton del RenderManager y la utiliza para
    /// crear una camara de Ogre que guarda en ogreCamera
    /// </summary>
    /// <param name="data"></param>
    FORGE_API bool initComponent(ComponentData* data) override;
    /// <summary>
    /// Crea una camara de Ogre que guarda en ogreCamera
    /// </summary>
    FORGE_API void onEnabled() override;
    /// <summary>
    /// Destruye la camara de Ogre asociada a este Camera
    /// </summary>
    FORGE_API void onDisabled() override;

	#pragma region setters
    /// <summary>
    /// Establece la distancia a la que se encuentra el plano de recorte cercano
    /// </summary>
    /// <param name="newNearClipDistance">Nueva distancia a la que se encuentra el plano de recorte cercano</param>
    FORGE_API void setNearClipDistance(float newNearClipDistance);
    /// <summary>
    /// Establece si la relacion de aspecto es automatica o no
    /// </summary>
    /// <param name="newAutoAspectRatio">Nuevo estado de la relacion de aspecto es automatica</param>
    FORGE_API void setAutoAspectRatio(bool newAutoAspectRatio);
    /// <summary>
    /// Establece el color de fondo
    /// </summary>
    /// <param name="newbackgroundColor">Nuevos valores RGB del fondo</param>
    FORGE_API void setBackgroundColor(forge::Vector3 const& newbackgroundColor);
	#pragma endregion

	#pragma region getters
    /// <summary>
    /// Devuelve la distancia a la que se encuentra el plano de recorte cercano
    /// </summary>
    /// <returns>Distancia a la que se encuentra el plano de recorte cercano</returns>
    const FORGE_API float& getNearClipDistance() const;
    /// <summary>
    /// Devuelve si la relacion de aspecto es automatica o no
    /// </summary>
    /// <returns>El estado de la relacion de aspecto automatica</returns>
    const FORGE_API bool& getAutoAspectRatio() const;
    /// <summary>
    /// Devuelve el color del fondo
    /// </summary>
    /// <returns>Un Vector3 con los valores RGB del fondo</returns>
    const FORGE_API forge::Vector3& getBackgroundColor() const;
	#pragma endregion
};

#endif // !CAMERA_H_
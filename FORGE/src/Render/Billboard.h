#pragma once
#ifndef BILLBOARD_H_
#define BILLBOARD_H_
#include <Component.h>
#include <Vector3.h>
#include <Vector2.h>
#include <string>

class RenderManager;
class Transform;
namespace Ogre {
    class BillboardSet;
}

class Billboard : public Component {
protected:
    forge::Vector2 billboardDimensions;
    std::string material;
    Ogre::BillboardSet* billboardSet;
    RenderManager& renderManager;
    Transform* transform;

    /// <summary>
    /// Intenta crear el node de Ogre para el BillboardSet y agregar un billboard a el
    /// </summary>
    /// <returns>Un booleano que indica si se ha podido crear el Billboard o no</returns>
    bool createBillboard();

public:
    FORGE_API_VAR static const std::string id;

    #pragma region Constructores
    FORGE_API Billboard();
    FORGE_API ~Billboard();
    #pragma endregion
    /// <summary>
    /// Crea el billboard
    /// </summary>
    FORGE_API void onEnabled() override;
    /// <summary>
    /// Borra el nodo de Ogre que contiene el BillboardSet
    /// </summary>
    FORGE_API void onDisabled() override;
    /// <summary>
    /// Inicializa el componente
    /// </summary>
    /// <param name="data"></param>
    /// <returns>Un booleano que indica si la inicialización fue correcta o no</returns>
    FORGE_API bool initComponent(ComponentData* data) override;

    #pragma region Getters
    /// <summary>
    /// Devuelve el numero de billboards que contiene el BillboardSet almacenado en la clase
    /// </summary>
    /// <returns>Numero de billboards contenidos</returns>
    FORGE_API int getSize();
    /// <summary>
    /// Acceso a la longitud de los billboards
    /// </summary>
    /// <returns>Devuelve la dimension en X de los billboards</returns>
    FORGE_API float getBillboardWidth();
    /// <summary>
    /// Acceso a la altura de los billboards
    /// </summary>
    /// <returns>Devuelve la dimension en Y de los billboards</returns>
    FORGE_API float getBillboardHeight();
    /// <summary>
    /// Acceso al material de los billboards almacenados en el billboardSet
    /// </summary>
    /// <returns>El nombre del material de los billboards</returns>
    FORGE_API std::string const& getMaterial();
    #pragma endregion

    #pragma region Setters
    /// <summary>
    /// Cambia el material de los billboards
    /// </summary>
    /// <param name="newMaterial">Nombre del nuevo material</param>
    FORGE_API void setMaterial(std::string const& newMaterial);
    #pragma endregion
};
#endif//BILLBOARD_H_
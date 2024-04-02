#pragma once
#ifndef BILLBOARD_H_
#define BILLBOARD_H_
#include <Component.h>
#include <Vector3.h>
#include <Vector2.h>
#include <string>

class RenderManager;
namespace Ogre {
    class BillboardSet;
}

class Billboard : public Component {
private:
    int size;
    forge::Vector2 billboardDimensions;
    forge::Vector3 totalDimensions;
    std::string material;
    Ogre::BillboardSet* billboardSet;
    RenderManager* renderManager;

public:
    static const std::string id;

    #pragma region Constructores
    Billboard();
    ~Billboard();
    #pragma endregion
    /// <summary>
    /// Activa el componente
    /// </summary>
    void onEnabled() override;
    /// <summary>
    /// Desactiva el componente
    /// </summary>
    void onDisabled() override;

    bool initComponent(ComponentData* data) override;

    /// <summary>
    /// Añade un nuevo billboard al conjunto
    /// </summary>
    void addBillboards();

    #pragma region Getters
    /// <summary>
    /// Devuelve el numero de billboards que contiene el BillboardSet almacenado en la clase
    /// </summary>
    /// <returns>Numero de billboards contenidos</returns>
    int getSize();
    /// <summary>
    /// Acceso a la longitud de los billboards
    /// </summary>
    /// <returns>Devuelve la dimension en X de los billboards</returns>
    float getBillboardWidth();
    /// <summary>
    /// Acceso a la altura de los billboards
    /// </summary>
    /// <returns>Devuelve la dimension en Y de los billboards</returns>
    float getBillboardHeight();
    /// <summary>
    /// Acceso al material de los billboards almacenados en el billboardSet
    /// </summary>
    /// <returns>El nombre del material de los billboards</returns>
    std::string getMaterial();
    #pragma endregion

    #pragma region Setters
    /// <summary>
    /// Cambia el material de los billboards
    /// </summary>
    /// <param name="newMaterial">Nombre del nuevo material</param>
    void setMaterial(std::string newMaterial);
    /// <summary>
    /// Cambia el tamaño del billboardSet (el número de billboards que puede contener)
    /// </summary>
    /// <param name="newSize">Nuevo tamaño del billboardSet</param>
    void setSize(int newSize);
    #pragma endregion
};
#endif//BILLBOARD_H_
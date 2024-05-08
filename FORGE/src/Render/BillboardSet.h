#pragma once
#ifndef BILLBOARD_SET_H
#define BILLBOARD_SET_H
#include "Billboard.h"

class BillboardSet : public Billboard {
protected:
    int size;
    forge::Vector3 totalDimensions;

    /// <summary>
    /// Intenta crear el node de Ogre para el BillboardSet y agregar varios billboards
    /// </summary>
    /// <param name = "number">El numero de billboards a crear</param>
    /// <returns>Un booleano que indica si se ha podido agregar los billboards</returns>
    bool addBillboards(int number);

public:
    FORGE_API_VAR static const std::string id;

    #pragma region Constructores
    FORGE_API BillboardSet();
    #pragma endregion
    /// <summary>
    /// Crea los billboards requeridos
    /// </summary>
    FORGE_API void onEnabled() override;
    /// <summary>
    /// Inicializa el componente
    /// </summary>
    /// <param name="data"></param>
    /// <returns>Un booleano que indica si se ha inicializado el componente correctamente</returns>
    FORGE_API bool initComponent(ComponentData* data) override;

    #pragma region Getters
    /// <summary>
    /// Devuelve el numero de billboards que contiene el BillboardSet almacenado en la clase
    /// </summary>
    /// <returns>Numero de billboards contenidos</returns>
    FORGE_API int const& getSize() const;
    #pragma endregion

    #pragma region Setters
    /// <summary>
    /// Cambia el tamaño del billboardSet (el número de billboards que puede contener)
    /// </summary>
    /// <param name="newSize">Nuevo tamaño del billboardSet</param>
    FORGE_API void setSize(int newSize);
    #pragma endregion
};
#endif // !BILLBOARD_SET_H
#pragma once
#ifndef FACTORY_H_
#define FACTORY_H_

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include "ForgeExport.h"
class Component;

class Factory : private std::unordered_map<std::string, std::function<Component*()>> {
private:
    static std::unique_ptr<Factory> instance;
public:
    /// <returns>Devuelve un puntero a la unica instancia de la clase</returns>
    FORGE_API static Factory* GetInstance();
    /// <summary>
    /// Almacena el nombre de un Component y una funcion que genera una instancia de ese Component para que se pueda crear desde el motor
    /// </summary>
    /// <typeparam name="ComponentType">Clase de un componente implementado heredado de Component</typeparam>
    /// <returns>Si se ha registrado correctamnte el Component</returns>
    template <class ComponentType>
    FORGE_API inline bool registerComponent() {
        return insert(std::pair<std::string, std::function<Component*()>>(ComponentType::id,
            [] () -> Component* {
                return new ComponentType();
            })
        ).second;
    }

    /// <summary>
    /// Crea una instancia del componente con nombre pedido
    /// </summary>
    /// <param name="compName">Nombre del componente que se quiere agregar</param>
    /// <returns>Un puntero a la instancia de componente creada</returns>
    FORGE_API Component* generateComponent(std::string const& id);

    FORGE_API void cleanUp();
};

#endif // !FACTORY_H_
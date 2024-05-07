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
    std::unordered_map<std::string, int> componentOrder;
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
        componentOrder.insert({ ComponentType::id, componentOrder.size()});
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
    /// <summary>
    /// Borra todas las funciones de la Factoria
    /// </summary>
    FORGE_API void cleanUp();
    /// <summary>
    /// Devuelve la cantidad de componentes registrados
    /// </summary>
    /// <returns>La cantidad de componentes registrados</returns>
    FORGE_API int getComponentAmount();
    /// <summary>
    /// Devuelve el orden de inicializacion del componente
    /// </summary>
    /// <returns>El orden de inicializacion del componente</returns>
    FORGE_API int getComponentOrder(std::string const& componentId);
    
};

#endif // !FACTORY_H_
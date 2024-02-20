#pragma once
#ifndef FACTORY_H_
#define FACTORY_H_

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
class Component;

class Factory : private std::unordered_map<std::string, std::function<Component*()>> {
    static std::unique_ptr<Factory> instance;
public:
    /// <returns>Devuelve un puntero a la única instancia de la clase</returns>
    static Factory* getInstance();
    /// <summary>
    /// Almacena el nombre de un Component y una función que genera una instancia de ese Component para que se pueda crear desde el motor
    /// </summary>
    /// <param name="compName">Nombre del Component a registrar</param>
    /// <param name="generator">Función que devuelve la instancia de un Component de ese tipo</param>
    /// <returns>Si se ha registrado correctamnte el Component</returns>
    /// <example>
    /// <code>
    /// registerComponent("Transform", 
    ///     []() -> Component* {
    ///         return new Transform();
    ///     }
    /// );
    /// </code>
    /// </example>
    bool registerComponent(std::string compName, std::function<Component*()> generator);
    /// <summary>
    /// Crea una instancia del componente con nombre pedido
    /// </summary>
    /// <param name="compName">Nombre del componente que se quiere añadir</param>
    /// <returns>Un puntero a la instancia de componente creada</returns>
    Component* generateComponent(std::string compName);
};

#endif // !FACTORY_H_

/*
 * @TODO:
 * (importante)
 * Para poder llamar a la función de inicialización de componentes desde la inicialización del motor
 * habería que tener una función callback por defecto vacía (nullptr) en el motor que se asigna en el 
 * archivo en el que se crea la función nueva chula de registerComponents
 * Ejemplo:
 * void registerComponents() {
 *  Factory::getInstance()->registerComponent("Transform", []()->Component*{
 *      return new Transform();
 *  });
 * }
 * 
 * forge->setComponentRegistrier(registerComponents);
*/
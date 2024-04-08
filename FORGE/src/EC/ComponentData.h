#pragma once
#ifndef COMPONENT_DATA_H_
#define COMPONENT_DATA_H_
#include <string>
#include <vector>
#include <unordered_set>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

class ComponentData {
private:
    template <typename T>
    struct getter {
        T operator()(luabridge::LuaRef& data, std::string const& param) {
            luabridge::LuaRef p = data[param];
            if (!p.isNil() && p.isInstance<T>()) {
                return p.cast<T>();
            }
            return T();
        }
    };
    template <typename U>
    struct getter<std::vector<U>> {
        std::vector<U> operator()(luabridge::LuaRef& data, std::string const& param) {
            luabridge::LuaRef table = data[param];
            std::vector<U> vec;
            if (table.isTable()) {
                for (auto&& pair : pairs(table)) {
                    vec.push_back(pair.second.cast<U>());
                }
            }
            return vec;
        }
    };
    template <typename U>
    struct getter<std::unordered_set<U>> {
        std::unordered_set<U> operator()(luabridge::LuaRef& data, std::string const& param) {
            luabridge::LuaRef table = data[param];
            std::unordered_set<U> set;
            if (table.isTable()) {
                for (auto&& pair : pairs(table)) {
                    set.insert(pair.second.cast<U>());
                }
            }
            return set;
        }
    };
protected:
    std::string id;
	luabridge::LuaRef* data;
public:
    /// <summary>
    /// Constructora por defecto de la clase ComponentData
    /// </summary>
    /// <param name="compId"> Identificador del componente </param>
    ComponentData(std::string const& _id);
	/// <summary>
	/// Constructora a partir de datos leidos de lua
	/// </summary>
	/// <param name="compId"> Identificador del componente </param>
	/// <param name="lrData"> Referencia a una LuaTable</param>
	ComponentData(std::string const& _id, luabridge::LuaRef* _data);
    /// <summary>
    /// Destruye la instancia de LuaRef apuntada
    /// </summary>
	~ComponentData();

    /// <returns>
    /// Identificador del componente
    /// </returns>
    std::string const& getId();

    bool has(std::string const& param);

    /// <summary>
    /// Devuelve el parametro pedido dentro del ComponentData
    /// </summary>
    /// <typeparam name="T">Tipo del valor a acceder</typeparam>
    /// <param name="param">Nombre del parametro al que se quiere acceder</param>
    /// <returns>
    /// El valor del parametro dentro del ComponentData. 
    /// Si no existe o no se puede castear devuelve el valor por defecto del tipo pedido.
    /// </returns>
    template <typename T>
    T get(std::string const& param) {
        return getter<T>()(*data, param);
    } 

    /// <summary>
    /// Get especifico para el tipo Vector2 de Forge
    /// </summary>
    /// <param name="param">Nombre del parametro al que se quiere acceder</param>
    /// <returns>El valor del parametro dentro del ComponentData convertido en forge::Vector2</returns>
    template <>
    forge::Vector2 get<forge::Vector2>(std::string const& param) {
        std::vector<float> input = getter<std::vector<float>>()(*data, param);
        forge::Vector2 vector = forge::Vector2();
        if (input.size() <= 2) {
            if (std::isinf(input[0]) || input.size() == 0) {
                input[0] = 0.0f;
                std::cerr << "ERROR: Valor del parametro 0 del Vector2 infinito o inexistente. Seteado a 0\n";
            }
            if (std::isinf(input[1]) || input.size() < 2) {
                input[1] = 0.0f;
                std::cerr << "ERROR: Valor del parametro 1 del Vector2 infinito o inexistente. Seteado a 0\n";
            }
        }
        else {
            std::cerr << "ERROR: Vector2 con mas de 2 parametros. Devolviendo los 2 primeros parametros\n";
        }
        vector = forge::Vector2(input[0], input[1]);    
        return vector;
    }
    /// <summary>
    /// Get especifico para el tipo Vector3 de Forge
    /// </summary>
    /// <param name="param">Nombre del parametro al que se quiere acceder</param>
    /// <returns>El valor del parametro dentro del ComponentData convertido en forge::Vector3</returns>
    template <>
    forge::Vector3 get<forge::Vector3>(std::string const& param) {
        std::vector<float> input = getter<std::vector<float>>()(*data,param);
        forge::Vector3 vector = forge::Vector3();
        if (input.size() <= 3) {
            if (std::isinf(input[0]) || input.size() == 0) {
                input[0] = 0.0f;
                std::cerr << "ERROR: Valor del parametro 0 del Vector3 infinito o inexistente. Seteado a 0\n";
            }
            if (std::isinf(input[1]) || input.size() < 2) {
				input[1] = 0.0f;
				std::cerr << "ERROR: Valor del parametro 1 del Vector3 infinito o inexistente. Seteado a 0\n";
			}
            if (std::isinf(input[2]) || input.size() < 3) {
                input[2] = 0.0f;
                std::cerr << "ERROR: Valor del parametro 2 del Vector3 infinito o inexistente. Seteado a 0\n";
            }
        }
        else {
            std::cerr << "ERROR: Vector3 con mas de 3 parametros. Devolviendo los 3 primeros parametros\n";
        }
        if (param == "scale") {
            if (input[0] == 0.0f) {
                input[0] = 1.0f;
                std::cerr << "ERROR: El valor en la X de la escala no puede ser 0. Seteado a 1\n";
            }
            if (input[1] == 0.0f) {
                input[1] = 1.0f;
                std::cerr << "ERROR: El valor en la Y de la escala no puede ser 0. Seteado a 1\n";
            }
            if (input[2] == 0.0f) {
                input[2] = 1.0f;
                std::cerr << "ERROR: El valor en la Z de la escala no puede ser 0. Seteado a 1\n";
            }
        }
        vector = forge::Vector3(input[0], input[1], input[2]);  
        return vector;
    }
    /// <summary>
    /// Get especifico para el tipo Quaternion de Forge
    /// </summary>
    /// <param name="param">Nombre del parametro al que se quiere acceder</param>
    /// <returns>El valor del parametro dentro del ComponentData convertido en forge::Quaternion</returns>
    template <>
    forge::Quaternion get<forge::Quaternion>(std::string const& param) {
        std::vector<float> input = getter<std::vector<float>>()(*data, param);
        forge::Quaternion quaternion = forge::Quaternion();
        if (input.size() <= 4) {
            if (std::isinf(input[0]) || input.size() == 0) {    
                input[0] = 0.0f;
                std::cerr << "ERROR: Valor del parametro 0 del Quaternion infinito o inexistente. Seteado a 0\n";  
            }
            if (std::isinf(input[1]) || input.size() < 2) { 
                input[1] = 0.0f;
                std::cerr << "ERROR: Valor del parametro 1 del Quaternion infinito o inexistente. Seteado a 0\n";  
            }
            if (std::isinf(input[2]) || input.size() < 3) { 
                input[2] = 0.0f;
                std::cerr << "ERROR: Valor del parametro 2 del Quaternion infinito o inexistente. Seteado a 0\n";  
            }
            if (std::isinf(input[2]) || input.size() < 4) {
                input[2] = 0.0f;
                std::cerr << "ERROR: Valor del parametro 2 del Quaternion infinito o inexistente. Seteado a 0\n";
            }
        }
        else {
            std::cerr << "ERROR: Quaternion con mas de 4 parametros. Devolviendo los 4 primeros parametros\n";
        }
        quaternion = forge::Quaternion(input[0], input[1], input[2], input[3]); 
        return quaternion;
    }


    /// <summary>
    /// Agrega un nuevo parametro a los datos del componente
    /// </summary>
    /// <typeparam name="T"> Tipo del parametro </typeparam>
    /// <param name="paramName"> Nombre del parametro </param>
    /// <param name="param"> Valor del parametro </param>
    template <typename T>
    void add(std::string const& paramName, T param) {
        (*data)[paramName] = param;
    }
};

#endif // !COMPONENT_DATA_H_


#pragma once
#ifndef COMPONENT_DATA_H_
#define COMPONENT_DATA_H_
#include <string>
#include <vector>
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include <Vector3.h>
#include <Quaternion.h>

__declspec(dllexport) class ComponentData {
private:
    template <typename T>
    struct getter {
        T operator()(luabridge::LuaRef& data, std::string param) {
            luabridge::LuaRef p = data[param];
            if (!p.isNil() && p.isInstance<T>()) {
                return p.cast<T>();
            }
            return T();
        }
    };
    template <typename U>
    struct getter<std::vector<U>> {
        std::vector<U> operator()(luabridge::LuaRef& data, std::string param) {
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
protected:
    std::string id;
	luabridge::LuaRef* data;
public:
    /// <summary>
    /// Constructora por defecto de la clase ComponentData
    /// </summary>
    /// <param name="compId"> Identificador del componente </param>
    ComponentData(std::string _id);
	/// <summary>
	/// Constructora a partir de datos leidos de lua
	/// </summary>
	/// <param name="compId"> Identificador del componente </param>
	/// <param name="lrData"> Referencia a una LuaTable</param>
	ComponentData(std::string _id, luabridge::LuaRef* _data);
    /// <summary>
    /// Destruye la instancia de LuaRef apuntada
    /// </summary>
	~ComponentData();

    /// <returns>
    /// Identificador del componente
    /// </returns>
    std::string getId();

    bool has(std::string param);

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
    T get(std::string param) {
        return getter<T>()(*data, param);
    } 

    template <>
    forge::Vector3 get<forge::Vector3>(std::string param) {
        std::vector<float> input = getter<std::vector<float>>()(*data,param);
        forge::Vector3 vector = forge::Vector3();
        if (input.size() >= 3) {
            vector = forge::Vector3(input[0], input[1], input[2]);
        }
        return vector;
    }

    template <>
    forge::Quaternion get<forge::Quaternion>(std::string param) {
        std::vector<float> input = getter<std::vector<float>>()(*data, param);
        forge::Quaternion quaternion = forge::Quaternion();
        if (input.size() >= 4) {
            quaternion = forge::Quaternion(input[0], input[1], input[2], input[3]);
        }
        return quaternion;
    }


    /// <summary>
    /// Agrega un nuevo parametro a los datos del componente
    /// </summary>
    /// <typeparam name="T"> Tipo del parametro </typeparam>
    /// <param name="paramName"> Nombre del parametro </param>
    /// <param name="param"> Valor del parametro </param>
    template <typename T>
    void add(std::string paramName, T param) {
        (*data)[paramName] = param;
    }
};

#endif // !COMPONENT_DATA_H_


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
#include "ForgeExport.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "ForgeError.h"
#include "ForgeFunction.h"

class ComponentData {
private:
    template <typename T>
    struct getter {
        getter() = delete;
        getter(getter const&) = delete;
        getter(getter &&) = delete;
        getter operator=(getter const&) = delete;
        getter operator=(getter &&) = delete;

        static T get(luabridge::LuaRef& data, std::string const& param) {
            luabridge::LuaRef p = data[param];
            if (!p.isNil() && p.isInstance<T>()) {
                return p.cast<T>();
            }
            return T();
        }
    };
    template <typename U>
    struct getter<std::vector<U>> {
        static std::vector<U> get(luabridge::LuaRef& data, std::string const& param) {
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
        static std::unordered_set<U> get(luabridge::LuaRef& data, std::string const& param) {
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
    template <typename U>
    struct getter<ForgeFunction<U>> {
        static ForgeFunction<U> get(luabridge::LuaRef& data, std::string const& param) {
            luabridge::LuaRef e = data[param];
            return ForgeFunction<U>(e);
        }
    };
    template <typename U>
    struct getter<ForgeFunction<U>*> {
        static ForgeFunction<U>* get(luabridge::LuaRef& data, std::string const& param) {
            luabridge::LuaRef e = data[param];
            return new ForgeFunction<U>(e);
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
    FORGE_API ComponentData(std::string const& _id);
	/// <summary>
	/// Constructora a partir de datos leidos de lua
	/// </summary>
	/// <param name="compId"> Identificador del componente </param>
	/// <param name="lrData"> Referencia a una LuaTable</param>
	FORGE_API ComponentData(std::string const& _id, luabridge::LuaRef* _data);
	/// <summary>
	/// Constructora por copia de ComponentData
	/// </summary>
	/// <param name="other">Instancia del ComponentData a copiar</param>
	FORGE_API ComponentData(ComponentData const& other);
    /// <summary>
    /// Destruye la instancia de LuaRef apuntada
    /// </summary>
    FORGE_API ~ComponentData();

    /// <returns>
    /// Identificador del componente
    /// </returns>
    FORGE_API std::string const& getId();

    /// <summary>
    /// Comprueba si existe un elemento con el nombre pasado en el ComponentData
    /// </summary>
    /// <returns>Booleano que indica si existe el elemento</returns>
    FORGE_API bool has(std::string const& param);

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
    FORGE_API inline T get(std::string const& param) {
        return getter<T>::get(*data, param);
    } 

    /// <summary>
    /// Get especifico para el tipo Vector2 de Forge
    /// </summary>
    /// <param name="param">Nombre del parametro al que se quiere acceder</param>
    /// <returns>El valor del parametro dentro del ComponentData convertido en forge::Vector2</returns>
    template <>
    FORGE_API inline forge::Vector2 get<forge::Vector2>(std::string const& param) {
        if ((*data)[param].isInstance<forge::Vector2>()) {
            return (*data)[param].cast<forge::Vector2>();
        }

        std::vector<float> input = getter<std::vector<float>>::get(*data, param);
        size_t i = 0;
        for (float& e : input) {
            if (i > 2) break;
            if (std::isinf(e) || input.size() < i + 1) {
                e = 0.0f;
                reportError("Valor del parametro " << i << " del Vector2 infinito o inexistente. Asignado a 0.");
            }
            ++i;
        }
        if (input.size() > 2) {
            reportError("Vector3 con mas de 2 parametros. Devolviendo los 2 primeros parametros.");
        }
        return forge::Vector2(input[0], input[1]);
    }
    /// <summary>
    /// Get especifico para el tipo Vector3 de Forge
    /// </summary>
    /// <param name="param">Nombre del parametro al que se quiere acceder</param>
    /// <returns>El valor del parametro dentro del ComponentData convertido en forge::Vector3</returns>
    template <>
    FORGE_API inline forge::Vector3 get<forge::Vector3>(std::string const& param) {
        if ((*data)[param].isInstance<forge::Vector3>()) {
            return (*data)[param].cast<forge::Vector3>();
        }

        std::vector<float> input = getter<std::vector<float>>::get(*data,param);
        size_t i = 0;
        for (float& e : input) {
            if (i > 3) break;
            if (std::isinf(e) || input.size() < i + 1) {
                e = 0.0f;
                reportError("Valor del parametro " << i << " del Vector3 infinito o inexistente. Asignado a 0.");
            }
            ++i;
        }
        if (input.size() > 3) {
            reportError("Vector3 con mas de 3 parametros. Devolviendo los 3 primeros parametros.");
        }
        return forge::Vector3(input[0], input[1], input[2]);
    }
    /// <summary>
    /// Get especifico para el tipo Quaternion de Forge
    /// </summary>
    /// <param name="param">Nombre del parametro al que se quiere acceder</param>
    /// <returns>El valor del parametro dentro del ComponentData convertido en forge::Quaternion</returns>
    template <>
    FORGE_API inline forge::Quaternion get<forge::Quaternion>(std::string const& param) {
        if ((*data)[param].isInstance<forge::Quaternion>()) {
            return (*data)[param].cast<forge::Quaternion>();
        }

        std::vector<float> input = getter<std::vector<float>>::get(*data, param);
        if (input.size() == 3) {
            return forge::Quaternion(getter<forge::Vector3>::get(*data, param));
        }
        size_t i = 0;
        for (float& e : input) {
            if (i > 4) break;
            if (std::isinf(e) || input.size() < i + 1) {
                e = 0.0f;
                reportError("Valor del parametro " << i << " del Quaternion infinito o inexistente. Asignado a 0.");
            }
            ++i;
        }
        if (input.size() > 4) {
            reportError("Quaternion con mas de 4 parametros. Devolviendo los 4 primeros parametros.");
        }
        return forge::Quaternion(input[0], input[1], input[2], input[3]);
    }


    /// <summary>
    /// Agrega un nuevo parametro a los datos del componente
    /// </summary>
    /// <typeparam name="T"> Tipo del parametro </typeparam>
    /// <param name="paramName"> Nombre del parametro </param>
    /// <param name="param"> Valor del parametro </param>
    template <typename T>
    FORGE_API inline void add(std::string const& paramName, T param) {
        (*data)[paramName] = param;
    }
};

#endif // !COMPONENT_DATA_H_


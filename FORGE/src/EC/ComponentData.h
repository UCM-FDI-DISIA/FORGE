#pragma once
#ifndef COMPONENT_DATA_H_
#define COMPONENT_DATA_H_
#include <string>
#include <vector>
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

class ComponentData {
protected:
    std::string id;
	luabridge::LuaRef* data;
public:
    /// <summary>
    /// Constructora por defecto de la clase ComponentData
    /// </summary>
    /// <param name="compId"> Identificador del componente </param>
    ComponentData(std::string compId);
	/// <summary>
	/// Constructora a partir de datos leidos de lua
	/// </summary>
	/// <param name="compId"> Identificador del componente </param>
	/// <param name="lrData"> Referencia a una LuaTable</param>
	ComponentData(std::string compId, luabridge::LuaRef* lrData);
    /// <summary>
    /// Destruye la instancia de LuaRef apuntada
    /// </summary>
	~ComponentData();

    /// <returns>
    /// Identificador del componente
    /// </returns>
    std::string getId();

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
        //bool is_vec = std::conditional < std::is_same<T, std::vector<typename T::value_type>>::value
        //if (is_vec) {
        //    return getVector(param);
        //}

        auto p = (*data)[param];
        if (!p.isNil() && p.isInstance<T>()) {
            return p.cast<T>();
        }
        return T();
    }

    //template <typename U>
    //std::vector<U> get<std::vector<U>>(std::string param) {
    //    std::vector<U> vec;
    //    auto t = (*data)[param];
    //    if (t.isTable()) {
    //        for (auto&& p : pairs(t)) {
    //            vec.push_back(p.first.cast<U>());
    //        }
    //    }
    //    return vec;
    //}

};

#endif // !COMPONENT_DATA_H_


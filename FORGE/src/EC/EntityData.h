#pragma once
#ifndef ENTITY_DATA_H_
#define ENTITY_DATA_H_
#include <unordered_map>
#include <string>

class ComponentData;

struct EntityData {
	bool isBlueprint;
	bool keepBetweenScenes;
	std::string group;
	std::string handler;
	std::vector<ComponentData*> components;
	std::unordered_map<std::string, int> componentMap;
	std::vector<EntityData*> children;
	/// <summary>
	/// Constructora por defecto, deja todo vacio
	/// </summary>
	EntityData();
	/// <summary>
	/// Constructora por copia a partir de otro EntityData
	/// </summary>
	/// <param name="other">Instancia de EntityData a copiar</param>
	EntityData(EntityData const& other);
	/// <summary>
	/// Elimina los ComponentData y los EntityData hijos de este que no sean blueprint.
	/// </summary>
	~EntityData();
};
#endif

#pragma once
#ifndef ECS_LOAD_H_
#define ECS_LOAD_H_

#include <string>
#include <vector>
#include <tuple>

class SceneManager;
class LuaForge;
struct EntityData;

namespace luabridge {
	class LuaRef;
}

class EcsLoad {
private:
	SceneManager& sceneManager;

	/// <summary>
	/// Establece los parametros necesarios para poder construir una Entidad.
	/// </summary>
	/// <param name="es">Estructura donde se guardan los parametros.</param>
	/// <param name="h">Entrada en lua con el la informacion de handler.</param>
	/// <param name="g">Entrada en lua con el la informacion de group.</param>
	/// <param name="cmps">Entrada en lua con la informacion de los componentes.</param>
	void extractEntityValues( EntityData& ed, luabridge::LuaRef& h, luabridge::LuaRef& g, luabridge::LuaRef& cmps );
	/// <summary>
	/// Modifica una entidad hija en una copia de un blueprint.
	/// </summary>
	/// <param name="cd">Estructura donde se guardan los parametros del hijo.</param>
	/// <param name="data">Entrada en lua con los datos de modificacion de la entidad.</param>
	void modifyChildrenData(EntityData& cd, luabridge::LuaRef& data);
	/// <summary>
	/// Agrega al EntityData los hijos asignados en Lua.
	/// </summary>
	/// <param name="es">Estructura donde se guardan los parametros.</param>
	/// <param name="children">Entrada en lua con los hijos de la entidad.</param>
	void extractChildren(EntityData& ed, luabridge::LuaRef& children);
	/// <summary>
	/// Lee una entidad de lua y la introduce en el SceneManager.
	/// </summary>
	/// <param name="data">Referencia a la tabla de lua con los datos.</param>
	/// <returns>Datos para construir una entidad.</returns>
	EntityData* parseEntityData( luabridge::LuaRef& data );
	/// <summary>
	/// Lee una escena de lua y la introduce en el SceneManager.
	/// </summary>
	/// <param name="data">Referencia a la tabla de lua con los datos.</param>
	/// <returns>Vector de datos de entidades para construir esta escena.</returns>
	std::vector<EntityData*> parseScene( luabridge::LuaRef& data );
public:
	/// <summary>
	/// Crea una instancia de EcsLoad que se encarga de leer desde un archivo lua toda la informacion 
	/// necesaria para que SceneManager pueda crear las escenas y entidades de nuestro juego.
	/// </summary>
	/// <param name="path"> 
	/// Ruta del archivo lua desde el que se va a cargar toda la informacion para SceneManager.
	/// </param>
	EcsLoad(std::string path, LuaForge& luaForge);

};

#endif // !ECS_LOAD_H_
#pragma once

#ifndef LOAD_MANAGER_H_
#define LOAD_MANAGER_H_

#include <string>
#include <vector>

class LuaForge;
class GameLoader;
class SceneManager;
class RenderManager;
class PhysicsManager;
class GUIManager;
struct EntityData;
class Factory;
namespace luabridge {
	class LuaRef;
}

class LoadManager {
private:
	LuaForge* luaForge;
	GameLoader* gameLoader;
	SceneManager& sceneManager;
	RenderManager& renderManager;
	PhysicsManager& physicsManager;
	GUIManager& guiManager;
	Factory& factory;
	/// <summary>
	/// Establece los parametros necesarios para poder construir una Entidad.
	/// </summary>
	/// <param name="entityData">Estructura donde se guardan los parametros.</param>
	/// <param name="handler">Entrada en lua con el la informacion de handler.</param>
	/// <param name="group">Entrada en lua con el la informacion de group.</param>
	/// <param name="components">Entrada en lua con la informacion de los componentes.</param>
	/// <returns>Booleano que indica si los valores de la entidad eran validos</returns>
	bool extractEntityValues(EntityData& entityData, luabridge::LuaRef& handler, luabridge::LuaRef& group, luabridge::LuaRef& components);
	/// <summary>
	/// Agrega al EntityData los hijos asignados en Lua.
	/// </summary>
	/// <param name="entityData">Estructura donde se guardan los parametros.</param>
	/// <param name="children">Entrada en lua con los hijos de la entidad.</param>
	/// <returns>Booleano que indica si se han extraido los hijos correctamente</returns>
	bool extractChildren(EntityData& entityData, luabridge::LuaRef& children);
	/// <summary>
	/// Modifica una entidad hija en una copia de un blueprint.
	/// </summary>
	/// <param name="childData">Estructura donde se guardan los parametros del hijo.</param>
	/// <param name="data">Entrada en lua con los datos de modificacion de la entidad.</param>
	bool modifyChildrenData(EntityData& childData, luabridge::LuaRef& data);
	/// <summary>
	/// Lee una entidad de lua y la introduce en el SceneManager.
	/// </summary>
	/// <param name="data">Referencia a la tabla de lua con los datos.</param>
	/// <returns>Datos para construir una entidad.</returns>
	EntityData* parseEntityData(luabridge::LuaRef& data);
	/// <summary>
	/// Lee una escena de lua y la introduce en el SceneManager.
	/// </summary>
	/// <param name="data">Referencia a la tabla de lua con los datos.</param>
	/// <returns>Vector de datos de entidades para construir esta escena.</returns>
	std::vector<EntityData*> parseScene(luabridge::LuaRef& data);
	/// <summary>
	/// Crea una instancia de EcsLoad que se encarga de leer desde un archivo lua toda la informacion 
	/// necesaria para que SceneManager pueda crear las escenas y entidades de nuestro juego.
	/// </summary>
	/// <param name="path"> 
	/// Ruta del archivo lua desde el que se va a cargar toda la informacion para SceneManager.
	/// </param>
	bool loadScenes(luabridge::LuaRef const& path);
	/// <summary>
	/// Carga los audios indicados en el archivo de recursos
	/// </summary>
	/// <returns>Booleano que indica si la carga se ha completado correctamente</returns>
	bool loadAudio();
	/// <summary>
	/// Carga la biblioteca del juego
	/// </summary>
	/// <param name="config">Referencia al LuaRef en el que se ha cargado la configuracion</param>
	/// <param name="gameName">string en el que se asignara el nombre del juego</param>
	/// <returns>Booleano que indica si la carga se ha completado correctamente</returns>
	bool loadGame(luabridge::LuaRef const& config, std::string& gameName);	/// <summary>
	/// Carga las dimensiones de la ventana del juego
	/// </summary>
	/// <param name="config">Referencia al LuaRef en el que se ha cargado la configuracion</param>
	/// <param name="gameName">string en el que se asignara el nombre del juego</param>
	/// <returns>Booleano que indica si la carga se ha completado correctamente</returns>
	bool loadWindow(uint32_t& width, uint32_t& height);
	/// <summary>
	/// Carga los componentes del juego que se hayan agregado a la Factory
	/// </summary>
	/// <returns>Booleano que indica si la carga se ha completado correctamente</returns>
	bool loadComponents();
	/// <summary>
	/// Carga desde el archivo de configuracion la configuracion de fisicas
	/// </summary>
	/// <returns>Booleano que indica si la carga se ha completado correctamente</returns>
	bool loadPhysics();
	/// <summary>
	/// Carga los recursos que haya en el archivo de recursos indicado en la configuracion
	/// </summary>
	/// <param name="config">Referencia al LuaRef en el que se ha cargado la configuracion</param>
	/// <returns>Booleano que indica si la carga se ha completado correctamente</returns>
	bool loadAssets(luabridge::LuaRef const& config);
	/// <summary>
	/// Carga la escena inicial indicada en el archivo de configuracion
	/// </summary>
	/// <param name="config">Referencia al LuaRef en el que se ha cargado la configuracion</param>
	/// <returns>Booleano que indica si la carga se ha completado correctamente</returns>
	bool loadInitialScene(luabridge::LuaRef const& config);
public:
	/// <summary>
	/// Crea el objeto de LoadManager y sus dependencias
	/// </summary>
	LoadManager();
	/// <summary>
	/// Inicializa todas las cargas del motor
	/// </summary>
	/// <param name="configFile">Ruta del archivo de configuracion del juego a cargar</param>
	/// <returns>Booleano que indica si se han podido cargar los datos</returns>
	bool init(std::string const& configFile);
	/// <summary>
	/// Se encarga de vaciar las cargas
	/// </summary>
	/// <returns>Booleano que indica si se ha limpiado bien</returns>
	bool cleanUp();
	/// <summary>
	/// Cierra las referencias a los archivos de carga
	/// </summary>
	~LoadManager();
};

#endif // !LOAD_MANAGER_H_
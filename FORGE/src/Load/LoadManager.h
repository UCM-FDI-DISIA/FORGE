#pragma once
#ifndef LOAD_MANAGER_H_
#define LOAD_MANAGER_H_
#include <string>
#include <vector>
class LuaForge;
class GameLoader;
class SceneManager;
class RenderManager;
struct EntityData;
namespace luabridge {
	class LuaRef;
}
class LoadManager {
private:
	LuaForge* luaForge;
	GameLoader* gameLoader;
	SceneManager& sceneManager;
	RenderManager& renderManager;
	std::string gameName;
	std::string initialScene;
	/// <summary>
	/// Establece los parametros necesarios para poder construir una Entidad.
	/// </summary>
	/// <param name="es">Estructura donde se guardan los parametros.</param>
	/// <param name="h">Entrada en lua con el la informacion de handler.</param>
	/// <param name="g">Entrada en lua con el la informacion de group.</param>
	/// <param name="cmps">Entrada en lua con la informacion de los componentes.</param>
	void extractEntityValues(EntityData& entityData, luabridge::LuaRef& handler, luabridge::LuaRef& group, luabridge::LuaRef& components);
	/// <summary>
	/// Modifica una entidad hija en una copia de un blueprint.
	/// </summary>
	/// <param name="cd">Estructura donde se guardan los parametros del hijo.</param>
	/// <param name="data">Entrada en lua con los datos de modificacion de la entidad.</param>
	void modifyChildrenData(EntityData& childData, luabridge::LuaRef& data);
	/// <summary>
	/// Agrega al EntityData los hijos asignados en Lua.
	/// </summary>
	/// <param name="es">Estructura donde se guardan los parametros.</param>
	/// <param name="children">Entrada en lua con los hijos de la entidad.</param>
	void extractChildren(EntityData& entityData, luabridge::LuaRef& children);
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
	/// 
	/// </summary>
	/// <returns></returns>
	bool loadAudio();
	bool loadGame(luabridge::LuaRef const& config);
	bool loadAssets(luabridge::LuaRef const& config);
	bool loadInitialScene(luabridge::LuaRef const& config);
public:
	LoadManager();
	/// <summary>
	/// Inicializa todas las cargas del motor
	/// </summary>
	/// <param name="assetsFile">Ruta del archivo en el que se indican los assets a cargar</param>
	/// <param name="scenesFile">Nombre del archivo de escenas dentro de Assets/scenes</param>
	bool init(std::string const& configFile);
	bool init(std::string const& assetsFile, std::string const& scenesFile);
	bool cleanUp();
	GameLoader& getGame();
	std::string const& getGameName() const;
	std::string const& getInitialScene() const;
	/// <summary>
	/// Cierra las referencias a los archivos de carga
	/// </summary>
	~LoadManager();
};

#endif // !LOAD_MANAGER_H_
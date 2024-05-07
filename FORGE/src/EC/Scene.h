#pragma once
#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
#include <unordered_map>
#include <string>
#include "ForgeExport.h"

class Entity;

class Scene {
protected:
    std::vector<std::vector<Entity*>> entitiesByGroup;
    std::unordered_map<std::string, Entity*> handlers;
public:
    /// <summary> 
    //// Constructor
    /// </summary>
    FORGE_API Scene();
    /// <summary>
    /// Destructor
	/// </summary>
    FORGE_API ~Scene();
    /// <summary>
    /// Actualiza las Entity de la escena
	/// </summary>
    FORGE_API void update();
    /// <summary>
	///	Actualiza la Entity en periodos de tiempo fijos
	/// </summary>
    FORGE_API void fixedUpdate();
    /// <summary>
    /// Borra todas las Entity no vivas
    /// </summary>
    FORGE_API void refresh();
    /// <summary>
    /// Inserta una nueva Entity a la escena con el grupo indicado
    /// </summary>
    /// <param name="groupId">Id del grupo que se le da a la Entity</param>
    /// <returns>La Entity creada. nullptr si no se pudo agregar</returns>
    FORGE_API Entity* addEntity(int groupId);
    /// <summary>
    /// Inserta una Entity ya existente a la escena
    /// </summary>
    /// <param name="entity">Entity ya existente</param>
    /// <returns>Entity insertada</returns>
    FORGE_API Entity* addEntity(Entity* entity);
    /// <returns>
    /// Una lista con todas las entidades en escena del grupo seleccionado
    /// </returns>
    FORGE_API std::vector<Entity*>& getEntitiesByGroup(int groupId);
    /// <returns>
    /// Una entidad en escena a partir de su handler. nullptr si no se encuentra
    /// </returns>
    FORGE_API Entity* getEntityByHandler(std::string const& handler);
    /// <summary>
    /// </summary>
    /// <param name="handler">Nombre que se le va a dar al Handler</param>
    /// <param name="entity">Entidad que se asocia al Handler</param>
    /// <returns>Booleano que indica si se ha podido agregar el Handler</returns>
    FORGE_API bool setHandler(std::string const& handler, Entity* entity);
    /// <summary>
    /// Desactiva la escena para cuando esta deja de estar activa
    /// </summary>
    /// <returns>Las entidades que se mantienen entre escenas</returns>
    FORGE_API std::vector<Entity*> disableScene();
    /// <summary>
    /// Activa la escena para cuando esta vuelve a estar activa
    /// </summary>
    FORGE_API void enableScene();
};
#endif // !COMPONENT_H_
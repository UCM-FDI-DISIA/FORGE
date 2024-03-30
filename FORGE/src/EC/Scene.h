#pragma once
#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
#include <unordered_map>
#include <string>

class Entity;

class Scene {
protected:
    std::vector<std::vector<Entity*>> entitiesByGroup;
    std::unordered_map<std::string, Entity*> handlers;
public:
    /// <summary> 
    //// Constructor
    /// </summary>
    Scene();
    /// <summary>
    /// Destructor
	/// </summary>
    virtual ~Scene();
    /// <summary>
    /// Actualiza las Entity de la escena
	/// </summary>
    virtual void update();
    /// <summary>
	///	Actualiza la Entity en periodos de tiempo fijos
	/// </summary>
    virtual void fixedUpdate();
    /// <summary>
    /// Borra todas las Entity no vivas
    /// </summary>
    void refresh();
    /// <summary>
    /// Inserta una nueva Entity a la escena con el grupo indicado
    /// </summary>
    /// <param name="groupId">Id del grupo que se le da a la Entity</param>
    /// <returns>La Entity creada</returns>
    Entity* addEntity(int groupId);
    /// <returns>
    /// Una lista con todas las entidades en escena del grupo seleccionado
    /// </returns>
    const std::vector<Entity*>& getEntitiesByGroup(int groupId);
    /// <returns>
    /// Una entidad en escena a partir de su handler
    /// </returns>
    const Entity* getEntityByHandler(std::string handler);
    /// <summary>
    /// </summary>
    /// <param name="handler">Nombre que se le va a dar al Handler</param>
    /// <param name="ent">Entidad que se asocia al Handler</param>
    /// <returns>Si se ha podido agregar el Handler</returns>
    bool setHandler(std::string handler, Entity* entity);
    /// <summary>
    ///	Establece si todos los Entity de la Scene estan activados
    /// </summary>
    /// <param name="_enabled">Nuevo estado de activacion de los Entities</param>
    void setEnabled(bool enabled);
};
#endif // !COMPONENT_H_
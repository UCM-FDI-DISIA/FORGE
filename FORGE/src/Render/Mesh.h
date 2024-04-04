#pragma once
#ifndef MESH_H_
#define MESH_H_
#include <Component.h>
#include <string>

class RenderManager;
namespace Ogre {
    class Entity;
}

class Mesh : public Component {
protected:
    std::string mesh;
    std::string material;
    Ogre::Entity* ogreEntity;
    RenderManager* renderManager; 

public:
	static const std::string id;

	/// <summary>
	/// Crea Mesh con valores por defecto
	/// </summary>
	Mesh();
    /// <summary>
    /// Destruye la entidad de Ogre asociada a este Mesh
    /// </summary>
    ~Mesh();

    /// <summary>
    /// Obtiene la referencia al singleton del RenderManager y la utiliza para
    /// crear una entidad de Ogre que guarda en ogreEntity
    /// </summary>
    /// <param name="data"></param>
    bool initComponent(ComponentData* data) override;
    /// <summary>
    /// Crea una entidad de Ogre que guarda en ogreEntity
    /// </summary>
    void onEnabled() override;
    /// <summary>
    /// Destruye la entidad de Ogre asociada a este Mesh
    /// </summary>
    void onDisabled() override;

	#pragma region setters
    /// <summary>
    /// Cambia la malla a partir de la que se crea la entidad de Ogre
    /// destruyendola y volviendola a crear
    /// </summary>
    /// <param name="newMesh">Nombre de la nueva malla</param>
    void setMesh(std::string newMesh);
    /// <summary>
    /// Cambia el material utilizado para la entidad de Ogre
    /// </summary>
    /// <param name="newMaterial">Nombre del nuevo material</param>
    void setMaterial(std::string newMaterial);
	#pragma endregion

	#pragma region getters
    /// <summary>
    /// Devuelve el nombre del archivo .mesh utilizado para la malla
    /// </summary>
    /// <returns>El nombre del archivo .mesh</returns>
    const std::string& getMesh() const;
    /// <summary>
    /// Obtiene el nombre del material utilizado
    /// </summary>
    /// <returns>El nombre del archivo .mesh</returns>
    const std::string& getMaterial() const;
	#pragma endregion
};

#endif // !MESH_H_
#pragma once
/// <summary>
/// Clase de manejo de los metodos de render
/// </summary>
#include <memory>
#include <unordered_map>
#include <string>

class RenderForge;
class Mesh;
class Camera;
class Light;
class Transform;

namespace Ogre {
	class Entity;
	class Camera;
	class Light;
	class Root;
	class SceneNode;
	class SceneManager;
	class MovableObject;
}


class RenderManager
{

private:
	static std::unique_ptr<RenderManager> instance;

	RenderForge* forge;
	Ogre::Root* root;        
	Ogre::SceneManager* sceneManager;

	std::unordered_map<Ogre::SceneNode*, Transform*> transforms;
	
	/// <summary>
	/// Constructora del render manager.
	/// </summary>
	RenderManager();


public:
	/// <summary>
	/// Destructora del RenderManager
	/// </summary>
	~RenderManager();

	/// <returns>Devuelve una instancia al RenderManager</returns>
	static RenderManager* getInstance();
#pragma region Setup
	/// <summary>
	/// Setup de una escena de prueba base, en el futuro se quitara esa parte y se hara que inicialice la ventana de Ogre sin mas.
	/// </summary>
	//<param name="name"> Nombre de la aplicacion</param>
	void setup(std::string appName);

	/// <summary>
	/// Renderiza un frame
	/// </summary>
	/// <returns>Devuelve True si ha podido renderizar</returns>
	bool render();
#pragma endregion


#pragma region ECS
	/// <summary>
	/// Añade un mesh a la escena
	/// </summary>
	/// <param name="mesh:">El mesh a añadir</param>
	/// <returns>Devuelve puntero de la entidad</returns>
	Ogre::Entity* addMeshNode(Mesh* mesh);
	
	/// <summary>
	/// Actualiza el mesh de una escena, cambiandolo por otro distinto
	/// </summary>
	/// <param name="entity:">La entidad a cambiar</param>
	/// <param name="mesh:">El mesh para sustituir</param>
	/// <returns>Devuelve puntero de la entidad</returns>
	Ogre::Entity* updateMeshNode(Ogre::Entity* entity, Mesh* mesh);

	/// <summary>
	/// Añade una camara a la escena
	/// </summary>
	/// <param name="camera:">La camara a añadir</param>
	/// <returns>Devuelve puntero de la camara</returns>
	Ogre::Camera* addCameraNode(Camera* camera);

	/// <summary>
	/// Añade una luz a la escena
	/// </summary>
	/// <param name="luz:">La luz a añadir</param>
	/// <returns>Devuelve puntero de la luz</returns>
	Ogre::Light* addLightNode(Light* light);

	/// <summary>
	/// Quita un nodo de la escena
	/// </summary>
	void removeNode(Ogre::MovableObject* entity);

#pragma endregion
};



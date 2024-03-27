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
class ParticleSystem;
class Transform;
class Billboard;

namespace Ogre {
	class Entity;
	class Camera;
	class Light;
	class BillboardSet;
	class ParticleSystem;
	class Root;
	class SceneNode;
	class SceneManager;
	class MovableObject;
	class NameGenerator;
}


class RenderManager
{

private:
	static std::unique_ptr<RenderManager> instance;

	RenderForge* forge;
	Ogre::Root* root;        
	Ogre::SceneManager* sceneManager;
	std::unordered_map<Ogre::SceneNode*, Transform*> transforms;

	//Generadores de nombres aleatorios
	Ogre::NameGenerator* cameraNames;
	Ogre::NameGenerator* particleSystemsNames;

	/// <summary>
	/// Constructora del render manager.
	/// </summary>
	RenderManager();

	void updateNodePositions();

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
	/// A�ade un mesh a la escena
	/// </summary>
	/// <param name="mesh:">El mesh a a�adir</param>
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
	/// A�ade un BillboardSet a la escena
	/// </summary>
	/// <param name="bs">El billboard a a�adir</param>
	/// <returns>Devuelve el puntero del BillboardSet</returns>
	Ogre::BillboardSet* addBillboardNode(Billboard* bs);


	//Ogre::BillboardSet* add(Ogre::BillboardSet bs, Billboard b);

	/// <summary>
	/// A�ade una camara a la escena
	/// </summary>
	/// <param name="camera:">La camara a a�adir</param>
	/// <returns>Devuelve puntero de la camara</returns>
	Ogre::Camera* addCameraNode(Camera* camera);

	/// <summary>
	/// A�ade una luz a la escena
	/// </summary>
	/// <param name="luz:">La luz a a�adir</param>
	/// <returns>Devuelve puntero de la luz</returns>
	Ogre::Light* addLightNode(Light* light);

	/// <summary>
	/// A�ade un sistema de particulas a la escena
	/// </summary>
	/// <param name="particleSystem:">El sistema de particulas a a�adir</param>
	/// <returns>Devuelve puntero del sistema de particulas</returns>
	Ogre::ParticleSystem* addParticleSystemNode(ParticleSystem* particleSystem);

	/// <summary>
	/// Actualiza el ParticleSystem de una escena, cambiandolo por otro distinto
	/// </summary>
	/// <param name="entity:">El ParticleSystem de ogre a cambiar</param>
	/// <param name="mesh:">El ParticleSystem con la informacion</param>
	/// <returns>Devuelve puntero del ParticleSystem de ogre</returns>
	Ogre::ParticleSystem* updateParticleSystemNode(Ogre::ParticleSystem* ogreParticleSystem, ParticleSystem* particleSystem);


	/// <summary>
	/// Quita un nodo de la escena
	/// </summary>
	void removeNode(Ogre::MovableObject* entity);

	void removeCamera(Ogre::Camera* camera);
#pragma endregion
};



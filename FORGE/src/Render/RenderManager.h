#pragma once

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

namespace forge {
	class Vector2;
	class Vector3;
	class Quaternion;
}

namespace Ogre {
	class Quaternion;
	template <int dims, typename T> class Vector;
	typedef Vector<3, float> Vector3f;
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
	class ManualObject;
}

class RenderManager {
private:
	static std::unique_ptr<RenderManager> instance;
	static bool initialised;

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

	/// <summary>
	/// Actualiza las posiciones de los nodos de OGRE que lo necesiten
	/// </summary>
	void updateNodePositions();

public:
	/// <summary>
	/// Crea una instancia del RenderManager
	/// </summary>
	/// <returns>Si la inicializacion fue correcta</returns>
	static void Init();
	/// <returns>Devuelve una instancia al RenderManager si existe, si no existe devuelve un puntero a nulo</returns>
	static RenderManager* GetInstance();
	RenderManager(RenderManager const&) = delete;
	void operator=(RenderManager const&) = delete;
	/// <summary>
	/// Destructora del RenderManager
	/// </summary>
	~RenderManager();

	#pragma region Setup
	/// <summary>
	/// Setup de una escena de prueba base, en el futuro se quitara esa parte y se hara que inicialice la ventana de OGRE sin mas.
	/// </summary>
	//<param name="name"> Nombre de la aplicacion</param>
	bool setup(std::string const& appName);

	/// <summary>
	/// Renderiza un frame
	/// </summary>
	/// <returns>Devuelve True si ha podido renderizar</returns>
	bool render();
	#pragma endregion


	#pragma region ECS
	/// <summary>
	/// Agrega un mesh a la escena
	/// </summary>
	/// <param name="mesh:">El mesh a agregar</param>
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
	/// Agrega un BillboardSet a la escena
	/// </summary>
	/// <param name="billboardSet">El conjunto de billboards a agregar</param>
	/// <returns>Devuelve el puntero del BillboardSet</returns>
	Ogre::BillboardSet* addBillboardNode(Billboard* billboardSet);

	/// <summary>
	/// Agrega una camara a la escena
	/// </summary>
	/// <param name="camera:">La camara a agregar</param>
	/// <returns>Devuelve puntero de la camara</returns>
	Ogre::Camera* addCameraNode(Camera* camera);

	/// <summary>
	/// Agrega una luz a la escena
	/// </summary>
	/// <param name="luz:">La luz a agragar</param>
	/// <returns>Devuelve puntero de la luz</returns>
	Ogre::Light* addLightNode(Light* light);

	/// <summary>
	/// Agrega un sistema de particulas a la escena
	/// </summary>
	/// <param name="particleSystem:">El sistema de particulas a agregar</param>
	/// <returns>Devuelve puntero del sistema de particulas</returns>
	Ogre::ParticleSystem* addParticleSystemNode(ParticleSystem* particleSystem);

	/// <summary>
	/// Actualiza el ParticleSystem de una escena, cambiandolo por otro distinto
	/// </summary>
	/// <param name="entity:">El ParticleSystem de OGRE a cambiar</param>
	/// <param name="mesh:">El ParticleSystem con la informacion</param>
	/// <returns>Devuelve puntero del ParticleSystem de OGRE</returns>
	Ogre::ParticleSystem* updateParticleSystemNode(Ogre::ParticleSystem* ogreParticleSystem, ParticleSystem* particleSystem);

	/// <summary>
	/// Elimina un nodo de OGRE de la escena
	/// </summary>
	/// <param name="entity">Entidad asociada al nodo que deseeamos eliminar</param>
	void removeNode(Ogre::MovableObject* entity);

	/// <summary>
	/// Quita un nodo de OGRE asociado a una CAMARA de la escena
	/// </summary>
	/// <param name="camera">Camara que queremos eliminar</param>
	void removeCamera(Ogre::Camera* camera);

	/// <summary>
	/// Actualiza el renderer para ajustarse al nuevo tamaño de la ventana
	/// </summary>
	void resizeWindow();
	#pragma endregion

	#pragma region Getters
	// <summary>
	/// Devuelve el sceneManager
	/// </summary>
	Ogre::SceneManager* getSceneManager();

	// <summary>
	/// Devuelve el tamano del renderer (la resolucion)
	/// </summary>
	forge::Vector2 getResolution();
	#pragma endregion
	
	#pragma region Utils
	Ogre::ManualObject* createManualObject(std::string const& name);
	#pragma endregion

	#pragma region Conversores
	Ogre::Quaternion forgeQuaternionToOgreQuaternion(forge::Quaternion const& v) const;
	Ogre::Vector3f forgeVector3ToOgreVector3(forge::Vector3 const& v) const;
	#pragma endregion
};
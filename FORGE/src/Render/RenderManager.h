#pragma once
/// <summary>
/// Clase de manejo de los metodos de render
/// </summary>
#include <memory>
#include <unordered_map>
#include <SDL_syswm.h>
#include <OgreString.h>

namespace Ogre {
	class FileSystemLayer;
	class Entity;
	class Camera;
	class Light;
	class Root;
	class SceneNode;
	class SceneManager;
	class RenderWindow;
	class MovableObject;
}

class Mesh;
class Camera;
class Light;
class Transform;

typedef SDL_Window NativeWindowType;


struct NativeWindowPair
{
	Ogre::RenderWindow* render = nullptr;
	NativeWindowType* native = nullptr;
};
	
class RenderManager
{

private:
	static std::unique_ptr<RenderManager> instance;

	Ogre::Root* myRoot;        
	NativeWindowPair myWindow; 

	Ogre::FileSystemLayer* myFileSystemLayer; 

	Ogre::String myAppName;
	Ogre::String mySolutionPath;
		
	Ogre::String myRTShaderLibPath;
	Ogre::SceneManager* mySceneManager;

	std::unordered_map<Ogre::SceneNode*, Transform*> transforms;

	RenderManager();

	/// <summary>
	/// Crea la root de Ogre y la devuelve.
	/// </summary>
	/// <returns>Devuelve el Root</returns>
	Ogre::Root* createRoot();


	/// <summary>
	/// Ubica donde estan los recursos para que los use el RenderManager
	/// </summary>
	void locateResources();


	//<summary>
	//Este metodo crea una ventana de SDL para renderizar OGRE
	//</summary>
	//<returns>Devuele la ventana de SDL y la de render de Ogre</returns>
	NativeWindowPair createWindow();

public:
	~RenderManager();

	static RenderManager* getInstance();
#pragma region Setup
	/// <summary>
	/// Setup de una escena de prueba base, en el futuro se quitara esa parte y se hara que inicialice la ventana de Ogre sin mas.
	/// </summary>
	//<param name="name"> Nombre de la aplicacion</param>
	void setup(Ogre::String appName);

	/// <summary>
	/// Renderiza un frame
	/// </summary>
	/// <returns>Devuelve True si ha podido renderizar</returns>
	bool render();

	/// <summary>
	/// Metodo para decir si el raton esta libre en la ventana
	/// </summary>
	/// <param name="_grab"></param>
	void setWindowGrab(bool active);
#pragma endregion


#pragma region ECS
/// <summary>
/// Añade un mesh a la escena
/// </summary>
/// <param name="mesh:">El mesh a añadir</param>
Ogre::Entity* addMeshNode(Mesh* mesh);
	
/// <summary>
/// Actualiza el mesh de una escena, cambiandolo por otro distinto
/// </summary>
/// <param name="entity:">La entidad a cambiar</param>
/// <param name="mesh:">El mesh para sustituir</param>
	Ogre::Entity* updateMeshNode(Ogre::Entity* entity, Mesh* mesh);

	Ogre::Camera* addCameraNode(Camera* camera);

	Ogre::Light* addLightNode(Light* camera);

	void removeNode(Ogre::MovableObject* entity);

#pragma endregion
};



#pragma once
/// <summary>
/// Clase de manejo de los metodos de render
/// </summary>
#include <SDL_syswm.h>
#include <OgreString.h>

namespace Ogre {
	class FileSystemLayer;
	class RenderWindow;
}

typedef SDL_Window NativeWindowType;


struct NativeWindowPair
{
	Ogre::RenderWindow* render = nullptr;
	NativeWindowType* native = nullptr;
};
	
class RenderForge
{

private:

	Ogre::Root* root;        
	NativeWindowPair window; 

	Ogre::FileSystemLayer* fileSystemLayer; 

	Ogre::String appName;
	Ogre::String solutionPath;
		
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

	/// <summary>
	/// Constructora del render manager.
	/// </summary>
	RenderForge(std::string appName);

	/// <summary>
	/// Destructora del RenderManager
	/// </summary>
	~RenderForge();

	Ogre::Root* getRoot();

	NativeWindowPair& getWindow();
	

};



#pragma once
#ifndef RENDER_FORGE_H_
#define RENDER_FORGE_H_
/// <summary>
/// Clase de manejo de los metodos de render
/// </summary>

#include <string>

namespace Ogre {
	class Root;
	class FileSystemLayer;
	class RenderWindow;
}

struct SDL_Window;
typedef SDL_Window NativeWindowType;

/// <summary>
/// <para>RenderWindow es donde OGRE renderiza.</para>
/// <para>NativeWindowType o SDL_Window es un struct de informacion de la ventana de SDL.</para>
/// </summary>
struct NativeWindowPair{
	Ogre::RenderWindow* render = nullptr;
	NativeWindowType* native = nullptr;
};
	
class RenderForge{
private:

	Ogre::Root* root;        
	NativeWindowPair window; 

	Ogre::FileSystemLayer* fileSystemLayer; 

	std::string appName;
	std::string solutionPath;
	
	#pragma region Setup
	/// <summary>
	/// Crea la root de Ogre y la devuelve.
	/// </summary>
	/// <returns>Devuelve el Root</returns>
	Ogre::Root* createRoot();

	/// <summary>
	/// Ubica donde estan los recursos para que los use el RenderManager
	/// </summary>
	void locateResources();

	/// <summary>
	/// Este metodo crea una ventana de SDL para renderizar OGRE
	/// </summary>
	/// <returns>Devuele la ventana de SDL y la de render de OGRE</returns>
	NativeWindowPair createWindow();
	#pragma endregion

public:
	/// <summary>
	/// Constructora de RenderForge
	/// </summary>
	/// <param name="appName:">Nombre de la aplicacion ejecutada</param>
	RenderForge(std::string const& appName);

	/// <summary>
	/// Destructora del RenderForge
	/// </summary>
	~RenderForge();

	#pragma region Getters
	/// <returns> Devuelve la raiz de OGRE</returns>
	Ogre::Root* getRoot();

	/// <returns> Devuelve el par de ventanas: La ventana nativa de SDL y la de ventana render de OGRE</returns>
	NativeWindowPair& getWindow();
	#pragma endregion
};

#endif // !RENDER_FORGE_H_
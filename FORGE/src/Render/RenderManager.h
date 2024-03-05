#pragma once

#include <OgreRoot.h>
#include <SDL.h>
#include <OgreFileSystemLayer.h>
#include <OgreBuildSettings.h>
#include <OgreLogManager.h>
#include <OgrePlugin.h>
#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <OgreRTShaderConfig.h>
#include <OgreRTShaderExports.h>

#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreDataStream.h>
#include <OgreEntity.h>

#include <SDL_video.h>
#include <SDL_syswm.h>

/// <summary>
/// Clase de manejo de los metodos de render
/// </summary>

namespace Render {
	
	typedef SDL_Window NativeWindowType;

	/**
	link between a renderwindow and a platform specific window
	*/
	struct NativeWindowPair
	{
		Ogre::RenderWindow* render = nullptr;
		NativeWindowType* native = nullptr;
	};
	
	class RenderManager
	{

	protected:
		Ogre::Root* myRoot;        
		NativeWindowPair myWindow; 

		Ogre::FileSystemLayer* myFileSystemLayer; 

		Ogre::String myAppName;
		Ogre::String mySolutionPath;
		
		Ogre::String myRTShaderLibPath;
		Ogre::SceneManager* mySceneManager = nullptr;

	public:
		RenderManager(std::string name);
		
		~RenderManager();


		NativeWindowPair createWindow( Ogre::String name );
		void setWindowGrab( bool active );

		void locateResources();
		bool renderOneFrame();

		void setup();

		Ogre::Root* getRoot();


	};
}



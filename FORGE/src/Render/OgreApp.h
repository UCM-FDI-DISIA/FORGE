#pragma once

#include <OgreRoot.h>
#include <SDL.h>
#include <OgreFileSystemLayer.h>
#include <OgreOverlaySystem.h>
#include <OgreBuildSettings.h>
#include <OgreLogManager.h>
#include <OgrePlugin.h>
#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <OgreRTShaderConfig.h>
#include <OgreRTShaderExports.h>

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


	class OgreApp : public Ogre::FrameListener {
	protected:
		Ogre::Root* mRoot;        // OGRE root
		NativeWindowPair mWindow; // the window

		Ogre::FileSystemLayer* mFSLayer; // File system abstraction layer
		Ogre::OverlaySystem* mOverlaySystem;  // Overlay system
		
		bool mFirstRun;
		Ogre::String mAppName;
		Ogre::String mSolutionPath;    // IG2: variable para hacer las rutas relativas al directorio de la solución
		
		Ogre::String mRTShaderLibPath;
		Ogre::SceneManager* mSM = nullptr;
		// Ogre::RTShader::ShaderGenerator* mShaderGenerator; // The Shader generator instance.
		// SGTechniqueResolverListener* mMaterialMgrListener; // Shader generator material manager listener.

	public:
		OgreApp();

		void go();
		void createRoot();
		void setup();

		NativeWindowPair createWindow(Ogre::String name);
		void setWindowGrab(bool active);   // IG2: ratón libre

		void locateResources();
		bool renderOneFrame();

		Ogre::Root* getRoot();
		bool isClosed();
		//bool initialiseRTShaderSystem();
	};
}

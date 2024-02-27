#include "OgreApp.h"


#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreDataStream.h>
#include <OgreEntity.h>

#include <SDL_video.h>
#include <SDL_syswm.h>

namespace Render {

	OgreApp::OgreApp() {
		mAppName = "FORGE";
		mFSLayer = new Ogre::FileSystemLayer(mAppName);
		mRoot = nullptr;
		mOverlaySystem = nullptr;
		mFirstRun = true;
	}

	void OgreApp::createRoot() {
		Ogre::String pluginsPath;
		pluginsPath = mFSLayer->getConfigFilePath("plugins.cfg");

		if (!Ogre::FileSystemLayer::fileExists(pluginsPath))
		{	// IG2: OGRE_CONFIG_DIR tiene un valor absoluto no portable
			//pluginsPath = Ogre::FileSystemLayer::resolveBundlePath(OGRE_CONFIG_DIR "/plugins" OGRE_BUILD_SUFFIX ".cfg");
			OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "IG2ApplicationContext::createRoot");
		}

		mSolutionPath = pluginsPath;    // IG2: añadido para definir directorios relativos al de la solución 
		mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);
		mFSLayer->setHomePath(mSolutionPath);   // IG2: para los archivos de configuración ogre. (en el bin de la solubión)
		mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);   // IG2: Quito /bin

		mRoot = new Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"), mFSLayer->getWritablePath("ogre.log"));

		mOverlaySystem = new Ogre::OverlaySystem();
	}

	void OgreApp::setup() {
		//mRoot->restoreConfig();  // IG2: no queremos que recupere la configuración guardada
		Ogre::RenderSystem* rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
		mRoot->setRenderSystem(rs);
		//rs->setConfigOption("Full Screen", "No");
		//rs->setConfigOption("Video Mode", "800 x 600");
		//rs->setConfigOption("sRGB Gamma Conversion", "Yes");
		//rs->setConfigOption("VSync", "No");
		//rs->setConfigOption("FSAA", "0");
		//rs->setConfigOption("RTT Preferred Mode", "FBO");
		mRoot->initialise(false);
		//Ogre::NameValuePairList misc;
		//misc["externalWindowHandle"] = Ogre::StringConverter::toString((int)0);
		//Ogre::RenderWindow* mWindow = mRoot->createRenderWindow("balls", 800, 600, false, &misc);
		auto mWindow = createWindow(mAppName);
		setWindowGrab(false);   // IG2: ratón libre

		locateResources();
		//initialiseRTShaderSystem();

		// adds context as listener to process context-level (above the sample level) events
		mRoot->addFrameListener(this);

		mSM = mRoot->createSceneManager();

		// register our scene with the RTSS
		//mShaderGenerator->addSceneManager(mSM);

		mSM->addRenderQueueListener(mOverlaySystem);

		mSM->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

		Ogre::Light* light = mSM->createLight("MainLight");
		Ogre::SceneNode* lightNode = mSM->getRootSceneNode()->createChildSceneNode();
		lightNode->attachObject(light);
		lightNode->setPosition(20, 80, 50);

		Ogre::SceneNode* camNode = mSM->getRootSceneNode()->createChildSceneNode();

		// create the camera
		Ogre::Camera* cam = mSM->createCamera("myCam");
		cam->setNearClipDistance(5); // specific to this sample
		cam->setAutoAspectRatio(true);
		camNode->attachObject(cam);
		camNode->setPosition(0, 0, 140);

		// and tell it to render into the main window
		Ogre::Viewport* vp = mWindow.render->addViewport(cam);
		vp->setBackgroundColour(Ogre::ColourValue(1, 0, 0));

		Ogre::Entity* ogreEntity = mSM->createEntity("ogrehead.mesh");
		Ogre::SceneNode* ogreNode = mSM->getRootSceneNode()->createChildSceneNode();
		ogreNode->attachObject(ogreEntity);
	}

	NativeWindowPair OgreApp::createWindow(Ogre::String name) {
		uint32_t w, h;
		Ogre::NameValuePairList miscParams;

		Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();

		std::istringstream mode(ropts["Video Mode"].currentValue);
		Ogre::String token;
		mode >> w; // width
		mode >> token; // 'x' as seperator between width and height
		mode >> h; // height

		miscParams["FSAA"] = ropts["FSAA"].currentValue;
		miscParams["vsync"] = ropts["VSync"].currentValue;
		miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

		if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

		Uint32 flags = SDL_WINDOW_RESIZABLE;

		if (ropts["Full Screen"].currentValue == "Yes")  flags = SDL_WINDOW_FULLSCREEN;
		//else  flags = SDL_WINDOW_RESIZABLE;

		mWindow.native = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(mWindow.native, &wmInfo);

		miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

		mWindow.render = mRoot->createRenderWindow(name, w, h, false, &miscParams);
		return mWindow;
	}

	void OgreApp::setWindowGrab(bool _grab)
	{
		SDL_bool grab = SDL_bool(_grab);
		SDL_SetWindowGrab(mWindow.native, grab);
		//SDL_SetRelativeMouseMode(grab);
		SDL_ShowCursor(grab);
	}

	void OgreApp::locateResources()
	{
		// load resource paths from config file
		Ogre::ConfigFile cf;

		Ogre::String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");
		if (Ogre::FileSystemLayer::fileExists(resourcesPath))
		{
			cf.load(resourcesPath);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				Ogre::FileSystemLayer::resolveBundlePath(mSolutionPath + "\\media"),
				"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		}

		Ogre::String sec, type, arch;
		// go through all specified resource groups
		Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
		for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
			// Esto sirve para dividir los recursos en secciones. Al comentarlo se van todos a "General"
			// sec = seci->first;
			const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

			// go through all resource paths
			for (i = settings.begin(); i != settings.end(); i++)
			{
				type = i->first;
				arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type); // El tercer parámetro sería "sec" si dividieramos en secciones
			}
		}

		sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

		// Aun no tenemos las excepciones de Ogre
		// OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

		arch = genLocs.front().archive->getName();
		type = genLocs.front().archive->getType();

		// Add locations for supported shader languages
		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
			}
			else
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
			}

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
			}
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
		}

		mRTShaderLibPath = arch + "/RTShaderLib";
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
		}

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	/*bool OgreApp::initialiseRTShaderSystem()
	{
		if (Ogre::RTShader::ShaderGenerator::initialize())
		{
			mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
			// Core shader libs not found -> shader generating will fail.
			if (mRTShaderLibPath.empty())
				return false;
			// Create and register the material manager listener if it doesn't exist yet.
			if (!mMaterialMgrListener) {
				mMaterialMgrListener = new SGTechniqueResolverListener(mShaderGenerator);
				Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
			}
		}

		return true;
	}*/

	bool OgreApp::go() {
		createRoot();
		setup();
		return mRoot->renderOneFrame();
	}
}
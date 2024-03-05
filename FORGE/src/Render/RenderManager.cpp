#include "RenderManager.h"

namespace Render {
	
	/// <summary>
	/// Constructora del RenderManager que crea la ventana y configura los parametros de archivos
	/// </summary>
	/// <param name="name"></param>
	RenderManager::RenderManager( std::string name ) {
		myAppName = name;
		myFileSystemLayer = new Ogre::FileSystemLayer( myAppName );
		myRoot = nullptr;

		//Crear Ogre Root
		Ogre::String pluginsPath;
		pluginsPath = myFileSystemLayer->getConfigFilePath( "plugins.cfg" );

		if (!Ogre::FileSystemLayer::fileExists( pluginsPath )) {
			OGRE_EXCEPT( Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "IG2ApplicationContext::createRoot" );
		}

		// Establecemos la ruta de los archivos de configuración en el sistema de archivos
		mySolutionPath = pluginsPath;
		mySolutionPath.erase( mySolutionPath.find_last_of( "\\" ) + 1, mySolutionPath.size() - 1 );
		myFileSystemLayer->setHomePath( mySolutionPath );
		mySolutionPath.erase( mySolutionPath.find_last_of( "\\" ) + 1, mySolutionPath.size() - 1 );

		// Creamos la raíz de OGRE 
		myRoot = new Ogre::Root( pluginsPath, myFileSystemLayer->getWritablePath( "ogre.cfg" ), myFileSystemLayer->getWritablePath( "ogre.log" ) );

		// Creamos el sistema de renderizado a partir del sistema de renderizado por defecto
		Ogre::RenderSystem* rs = myRoot->getRenderSystemByName( "OpenGL Rendering Subsystem" );
		myRoot->setRenderSystem( rs );

		// Inicializamos el sistema de renderizado
		myRoot->initialise( false );

		// Creamos la ventana
		auto mWindow = createWindow( myAppName );
		setWindowGrab( false );
	}
	
	//<summary>
	 //Este metodo crea una ventana de SDL para renderizar OGRE
	 //</summary>
	 //<param name="name"></param>
	 //<returns>Devuele la ventana de SDL y la de render de Ogre</returns>
	NativeWindowPair RenderManager::createWindow( Ogre::String name ) {
		uint32_t w, h;
		Ogre::NameValuePairList miscParams;

		Ogre::ConfigOptionMap ropts = myRoot->getRenderSystem()->getConfigOptions();

		std::istringstream mode( ropts["Video Mode"].currentValue );
		Ogre::String token;
		mode >> w; 
		mode >> token; 
		mode >> h; 

		miscParams["FSAA"] = ropts["FSAA"].currentValue;
		miscParams["vsync"] = ropts["VSync"].currentValue;
		miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

		if (!SDL_WasInit( SDL_INIT_VIDEO )) SDL_InitSubSystem( SDL_INIT_VIDEO );

		// Establecemos la ventana como redimensionable por defecto
		Uint32 flags = SDL_WINDOW_RESIZABLE;

		// Si la opción de pantalla completa está activada, la ventana se establece como pantalla completa
		if (ropts["Full Screen"].currentValue == "Yes")  flags = SDL_WINDOW_FULLSCREEN;

		// Creamos la ventana nativa de SDL
		myWindow.native = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags );

		// Establecemos los parámetros de la ventana de render y la creamos
		SDL_SysWMinfo wmInfo;
		SDL_VERSION( &wmInfo.version );
		SDL_GetWindowWMInfo( myWindow.native, &wmInfo );
		miscParams["externalWindowHandle"] = Ogre::StringConverter::toString( size_t( wmInfo.info.win.window ) );
		myWindow.render = myRoot->createRenderWindow( name, w, h, false, &miscParams );
		return myWindow;
	}

	/// <summary>
	/// Metodo para decir si el raton esta libre en la ventana
	/// </summary>
	/// <param name="_grab"></param>
	void RenderManager::setWindowGrab( bool _grab ) {
		// Establecemos el ratón como libre o no
		SDL_bool grab = SDL_bool( _grab );
		SDL_SetWindowGrab( myWindow.native, grab );
		SDL_ShowCursor( grab );
	}

	/// <summary>
	/// Ubica donde estan los recursos para que los use el RenderManager
	/// </summary>
	void RenderManager::locateResources() {
		// Cargamos los recursos del archivo resources.cfg
		Ogre::ConfigFile cf;

		Ogre::String resourcesPath = myFileSystemLayer->getConfigFilePath( "resources.cfg" );
		if (Ogre::FileSystemLayer::fileExists( resourcesPath )) {
			cf.load( resourcesPath );
		}
		else {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				Ogre::FileSystemLayer::resolveBundlePath( mySolutionPath + "\\media" ),
				"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
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
			for (i = settings.begin(); i != settings.end(); i++) {
				type = i->first;
				arch = Ogre::FileSystemLayer::resolveBundlePath( i->second );
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation( arch, type ); // El tercer parámetro sería "sec" si dividieramos en secciones
			}
		}

		sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList( sec );

		// Aun no tenemos las excepciones de Ogre
		// OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

		arch = genLocs.front().archive->getName();
		type = genLocs.front().archive->getType();

		// Add locations for supported shader languages
		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported( "glsles" )) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( arch + "/materials/programs/GLSLES", type, sec );
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported( "glsl" )) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( arch + "/materials/programs/GLSL120", type, sec );

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported( "glsl150" )) {
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation( arch + "/materials/programs/GLSL150", type, sec );
			}
			else {
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation( arch + "/materials/programs/GLSL", type, sec );
			}

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported( "glsl400" )) {
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation( arch + "/materials/programs/GLSL400", type, sec );
			}
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported( "hlsl" )) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( arch + "/materials/programs/HLSL", type, sec );
		}

		myRTShaderLibPath = arch + "/RTShaderLib";
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation( myRTShaderLibPath + "/materials", type, sec );

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported( "glsles" )) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( myRTShaderLibPath + "/GLSL", type, sec );
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( myRTShaderLibPath + "/GLSLES", type, sec );
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported( "glsl" )) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( myRTShaderLibPath + "/GLSL", type, sec );
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported( "hlsl" )) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( myRTShaderLibPath + "/HLSL", type, sec );
		}

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	/// <summary>
	/// Renderiza un frame
	/// </summary>
	/// <returns>Devuelve True si ha podido renderizar</returns>
	bool RenderManager::renderOneFrame() {
		return myRoot->renderOneFrame();
	}

	
	Ogre::Root* RenderManager::getRoot() {
		return myRoot;
	}

	void RenderManager::setup() {

		// Creamos el sistema de renderizado a partir del sistema de renderizado por defecto
		Ogre::RenderSystem* rs = myRoot->getRenderSystemByName( "OpenGL Rendering Subsystem" );
		myRoot->setRenderSystem( rs );

		// Inicializamos el sistema de renderizado
		myRoot->initialise( false );

		// Creamos la ventana
		auto mWindow = createWindow( myAppName );
		setWindowGrab( false );

		// Inicializamos los recursos
		locateResources();

		// Creamos la escena
		mySceneManager = myRoot->createSceneManager();
		mySceneManager->setAmbientLight( Ogre::ColourValue( 0.5, 0.5, 0.5 ) );

		// Creamos una luz
		Ogre::Light* light = mySceneManager->createLight( "MainLight" );
		Ogre::SceneNode* lightNode = mySceneManager->getRootSceneNode()->createChildSceneNode();
		lightNode->attachObject( light );
		lightNode->setPosition( 20, 80, 50 );

		// Creamos una cámara
		Ogre::SceneNode* camNode = mySceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Camera* cam = mySceneManager->createCamera( "myCam" );
		cam->setNearClipDistance( 5 );
		cam->setAutoAspectRatio( true );
		camNode->attachObject( cam );
		camNode->setPosition( 0, 0, 140 );

		// Creamos un viewport y cambiamos el color de fondo
		Ogre::Viewport* vp = mWindow.render->addViewport( cam );
		vp->setBackgroundColour( Ogre::ColourValue( 1, 0, 0 ) );

		// Creamos una entidad y la añadimos a la escena
		Ogre::Entity* ogreEntity = mySceneManager->createEntity( "ogrehead.mesh" );
		Ogre::SceneNode* ogreNode = mySceneManager->getRootSceneNode()->createChildSceneNode();
		ogreNode->attachObject( ogreEntity );
	}
}

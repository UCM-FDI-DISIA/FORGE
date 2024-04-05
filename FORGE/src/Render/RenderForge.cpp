#include "RenderForge.h"
#include <iostream>
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
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
#include <OgreDataStream.h>
#include <OgreString.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#pragma warning(pop)


Ogre::Root* RenderForge::createRoot() {
	fileSystemLayer = new Ogre::FileSystemLayer(appName);

	Ogre::String pluginsPath;
	pluginsPath = fileSystemLayer->getConfigFilePath("plugins.cfg");

	if (!Ogre::FileSystemLayer::fileExists(pluginsPath)) {
		std::cerr << "ERROR: No se ha encontrado el archivo de plugins" << std::endl;
		correctInitialitation = false;
		return nullptr;
	}

	solutionPath = pluginsPath;
	solutionPath.erase(solutionPath.find_last_of("\\") + 1, solutionPath.size() - 1);
	fileSystemLayer->setHomePath(solutionPath);

	// Creamos la raíz de OGRE 
	return new Ogre::Root(pluginsPath, fileSystemLayer->getWritablePath("ogre.cfg"), fileSystemLayer->getWritablePath("ogre.log"));
}

void RenderForge::locateResources() {
	// Cargamos los recursos del archivo resources.cfg
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = fileSystemLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath)) {
		cf.load(resourcesPath);
	}
	else {
		correctInitialitation = false;
		std::cerr << "ERROR: No se localizaron los recursos\n";
		return;
	}

	Ogre::String sec, type, arch;
	// Iterar sobre todos los grupos de recursos
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		// Esto sirve para dividir los recursos en secciones. Al comentarlo se van todos a "General"
		// sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		
		// iterar por todas las rutas de configuracion
		for (auto& i : settings) {
			type = i.first;
			arch = i.second;
			if (arch[0] == '.' && (arch[1] == '/' || arch[1] == '\\' ||
					(arch[1] == '.' && (arch[2] == '/' || arch[2] == '\\')))) {
				arch = fileSystemLayer->getWritablePath(arch);
			}
			arch = Ogre::FileSystemLayer::resolveBundlePath(arch);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type); // El tercer parámetro sería "sec" si dividieramos en secciones
		
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	// Aun no tenemos las excepciones de Ogre
	// OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	arch = genLocs.front().archive->getName();
	type = genLocs.front().archive->getType();

	// Anadir las ubicaciones de todos los lenguajes de shaders con soporte
	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles")) {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl")) {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150")) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400")) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl")) {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}

	Ogre::String rtShaderLibPath = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(rtShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles")) {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(rtShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(rtShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl")) {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(rtShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl")) {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(rtShaderLibPath + "/HLSL", type, sec);
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

NativeWindowPair RenderForge::createWindow() {
	uint32_t w, h;
	Ogre::NameValuePairList miscParams;

	if (root == nullptr) return { nullptr, nullptr };

	Ogre::ConfigOptionMap ropts = root->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> w;
	mode >> token;
	mode >> h;

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		SDL_InitSubSystem(SDL_INIT_VIDEO);
	}
	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (ropts["Full Screen"].currentValue == "Yes") {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	window.native = SDL_CreateWindow(appName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	// Establecemos los parametros de la ventana de render y la creamos
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window.native, &wmInfo);
	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
	window.render = root->createRenderWindow(appName, w, h, false, &miscParams);
	return window;
}

RenderForge::RenderForge(std::string const& _appName) :
	root(nullptr),
	window({nullptr, nullptr}),
	fileSystemLayer(nullptr),
	appName(_appName),
	solutionPath() {
	correctInitialitation = true;
	
	root = createRoot();

	if (correctInitialitation) {
		// Creamos el sistema de renderizado a partir del sistema de renderizado por defecto
		try {
			Ogre::RenderSystem* rs = root->getRenderSystemByName("OpenGL Rendering Subsystem");
			root->setRenderSystem(rs);
		}
		catch (std::exception e) {
			correctInitialitation = false;
			std::cerr << "ERROR: Fallo al asignar el Render System\n";
		}

		if (correctInitialitation) {
			// Inicializamos el sistema de renderizado
			try {
				root->initialise(false);
			} 
			catch (std::exception e) {
				correctInitialitation = false;
				std::cerr << "ERROR: Fallo al inicializar root\n";
			}
			
			if (correctInitialitation) {
				// Creamos la ventana
				window = createWindow();
				if (window.render == nullptr || window.native == nullptr) {
					correctInitialitation = false;
					std::cerr << "ERROR: Fallo en la creacion de la ventana\n";
				}

				if (correctInitialitation) {
					// Inicializamos los recursos
					locateResources();
				}
			}
		}
	}
}

RenderForge::~RenderForge() {
	delete fileSystemLayer;
	delete root;
}

Ogre::Root* RenderForge::getRoot() {
	return root;
}

NativeWindowPair& RenderForge::getWindow() {
	return window;
}

bool RenderForge::getInitialitation() { 
	return correctInitialitation;
}

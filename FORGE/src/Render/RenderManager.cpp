#include "RenderManager.h"
#include "RenderForge.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "Entity.h"
#include "Transform.h"
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
#include <OgreEntity.h>
#include <iostream>
#include <OgreViewport.h>

std::unique_ptr<RenderManager> RenderManager::instance = nullptr;


RenderManager::RenderManager() : 
	forge(nullptr),
	root(nullptr),
	sceneManager(nullptr),
	transforms() {

}

RenderManager::~RenderManager() {
	delete myFileSystemLayer;
	delete myRoot;
}


Ogre::Root* RenderManager::createRoot() {
	myFileSystemLayer = new Ogre::FileSystemLayer(myAppName);

	// Crear Ogre Root
	Ogre::String pluginsPath;
	pluginsPath = myFileSystemLayer->getConfigFilePath("plugins.cfg");

	// Si no existe el archivo de plugins se le dice al usuario que no se ha encontrado
	if (!Ogre::FileSystemLayer::fileExists(pluginsPath)) {
		std::cerr << "ERROR: No se ha encontrado el archivo de plugins" << std::endl;
		return nullptr;
	}

	// Establecemos la ruta de los archivos de configuración en el sistema de archivos
	mySolutionPath = pluginsPath;
	mySolutionPath.erase(mySolutionPath.find_last_of("\\") + 1, mySolutionPath.size() - 1);
	myFileSystemLayer->setHomePath(mySolutionPath);
	mySolutionPath.erase(mySolutionPath.find_last_of("\\") + 1, mySolutionPath.size() - 1);

	// Creamos la raíz de OGRE 
	return new Ogre::Root(pluginsPath, myFileSystemLayer->getWritablePath("ogre.cfg"), myFileSystemLayer->getWritablePath("ogre.log"));
}

NativeWindowPair RenderManager::createWindow() {
	uint32_t w, h;
	Ogre::NameValuePairList miscParams;

	if(myRoot == nullptr) return {nullptr, nullptr};

	// Obtenemos las opciones de configuración del sistema de renderizado
	Ogre::ConfigOptionMap ropts = myRoot->getRenderSystem()->getConfigOptions();

	// Obtenemos el modo de vídeo y lo parseamos
	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> w;
	mode >> token;
	mode >> h;

	// Establecemos los parámetros de la ventana
	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

	// Establecemos la ventana como redimensionable por defecto
	Uint32 flags = SDL_WINDOW_RESIZABLE;

	// Si la opción de pantalla completa está activada, la ventana se establece como pantalla completa
	if (ropts["Full Screen"].currentValue == "Yes")  flags = SDL_WINDOW_FULLSCREEN;

	// Creamos la ventana nativa de SDL
	myWindow.native = SDL_CreateWindow(myAppName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	// Establecemos los parámetros de la ventana de render y la creamos
	SDL_SysWMinfo wmInfo = { 0 };
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(myWindow.native, &wmInfo);
	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
	myWindow.render = myRoot->createRenderWindow(myAppName, w, h, false, &miscParams);
	return myWindow;
}

void RenderManager::locateResources() {
	// Cargamos los recursos del archivo resources.cfg
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = myFileSystemLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath)) {
		cf.load(resourcesPath);
	}
	else {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(mySolutionPath + "\\media"),
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
		for (i = settings.begin(); i != settings.end(); i++) {
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

	myRTShaderLibPath = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(myRTShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles")) {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(myRTShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(myRTShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl")) {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(myRTShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl")) {
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(myRTShaderLibPath + "/HLSL", type, sec);
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	delete forge;
}

RenderManager* RenderManager::getInstance() {
	if (instance.get() != nullptr) return instance.get();
	return (instance = std::unique_ptr<RenderManager>(new RenderManager())).get();
}

void RenderManager::setup(std::string appName) {
	forge = new RenderForge(appName);
	root = forge->getRoot();
	if (root == nullptr) return;
	// Creamos la escena
	sceneManager = root->createSceneManager();
	sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

bool RenderManager::render() {
	if(myRoot == nullptr) return false;
	for (auto&& pair : transforms) {
		if (pair.second->getNeedsUpdate()) {
			const forge::Vector3& position = pair.second->getGlobalPosition();
			pair.first->setPosition(position);
			const forge::Quaternion& rotation = pair.second->getGlobalRotation();
			pair.first->setOrientation(rotation);
			const forge::Vector3& scale = pair.second->getGlobalScale();
			pair.first->setScale(scale);
			pair.second->setNeedsUpdate(false);
		}
	}
	return root->renderOneFrame();
}


Ogre::Entity* RenderManager::addMeshNode(Mesh* mesh) {
	if(myRoot == nullptr) return nullptr;
	try {
		Ogre::Entity* entity = sceneManager->createEntity(mesh->getMesh());
		Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
		if (mesh->getMaterial() != "") {
			entity->setMaterialName(mesh->getMaterial());
		}
		node->attachObject(entity);
		transforms.insert({ node, mesh->getEntity()->getComponent<Transform>() });
		return entity;
	}
	catch (std::exception e) {
		std::cerr << "ERROR: No se ha podido cargar un mesh " << mesh->getMesh() << "\n";
		return nullptr;
	}
}


Ogre::Entity* RenderManager::updateMeshNode(Ogre::Entity* entity, Mesh* mesh) {
	Ogre::SceneNode* node = entity->getParentSceneNode();
	node->detachObject(entity);
	sceneManager->destroyEntity(entity);
	Ogre::Entity* newEntity = sceneManager->createEntity(mesh->getMesh());
	if (mesh->getMaterial() != "") {
		newEntity->setMaterialName(mesh->getMaterial());
	}
	node->attachObject(entity);
	return newEntity;
}

Ogre::Camera* RenderManager::addCameraNode(Camera* camera) {
	if(myRoot == nullptr) return nullptr;
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::Camera* ogreCamera = sceneManager->createCamera(camera->getName());
	ogreCamera->setNearClipDistance(camera->getNearClipDistance());
	ogreCamera->setAutoAspectRatio(camera->getAutoAspectRatio());
	node->attachObject(ogreCamera);
	Ogre::Viewport* viewport = forge->getWindow().render->addViewport(ogreCamera);
	Ogre::ColourValue value = Ogre::ColourValue(
		camera->getBackgroundColor().getX(),
		camera->getBackgroundColor().getY(),
		camera->getBackgroundColor().getZ());
	viewport->setBackgroundColour(value);
	transforms.insert({ node, camera->getEntity()->getComponent<Transform>() });
	return ogreCamera;
}

Ogre::Light* RenderManager::addLightNode(Light* light) {
	if (myRoot == nullptr) return nullptr;
	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::Light* ogreLight = sceneManager->createLight(Ogre::Light::LightTypes(light->getType()));
	node->attachObject(ogreLight);
	transforms.insert({ node, light->getEntity()->getComponent<Transform>() });
	return ogreLight;
}

void RenderManager::removeNode(Ogre::MovableObject* object) {
	if(myRoot == nullptr) return;
	Ogre::SceneNode* node = object->getParentSceneNode();
	node->detachObject(object);
	sceneManager->destroyEntity(object);
	sceneManager->destroySceneNode(node);
	transforms.erase(node);
}



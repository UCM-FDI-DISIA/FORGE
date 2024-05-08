#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Component.h"
#include "ComponentData.h"
#include "EntityData.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "Transform.h"
#include "ForgeError.h"
#include "Factory.h"

SceneManager::EntityPair::~EntityPair() {
	for (auto& child : children) {
		delete child;
	}
}

std::unique_ptr<SceneManager> SceneManager::instance = nullptr;
bool SceneManager::initialised = false;

SceneManager::SceneManager() : 
	activeScene("",nullptr),
	lua(nullptr) {
	groups.insert({"default",0});
}

SceneManager::EntityPair* SceneManager::addEntity(Scene* scene, EntityData* data) {
	Entity* entity = scene->addEntity(getGroupId(data->group));

	EntityPair* pair = new EntityPair();
	pair->entity = entity;
	pair->data = data;

	if (data->handler != "") {
		scene->setHandler(data->handler, entity);
	}
	if (data->keepBetweenScenes) {
		entity->setKeepBetweenScenes(true);
	}
	for (auto& componentData : data->components) {
		if (componentData != nullptr) {
			Component* component = entity->addComponent(componentData->getId());
			if (component == nullptr) {
				entity->setAlive(false);
			}
		}
	}
	for (auto& childData : data->children) {
		if (childData != nullptr) {
			EntityPair* child = addEntity(scene, childData);
			if (!child->entity->isAlive()) {
				entity->setAlive(false);
			}
			entity->addChild(child->entity);
			pair->children.push_back(child);
		}
	}

	return pair;
}

Entity* SceneManager::initEntity(EntityPair* pair) {
	if (!pair->entity->initSerializedComponents(pair->data->components)) {
		pair->entity->setAlive(false);
	}
	if (!pair->entity->initComponents(pair->data->components)) {
		pair->entity->setAlive(false);
	}
	for (auto& child : pair->children) {
		initEntity(child);
	}
	return pair->entity;
}

Entity* SceneManager::instantiateBlueprint(EntityData* data) {
	if (data == nullptr) {
		throwError(nullptr, "No se ha encontrado el BluePrint espeficiado");
	}
	Scene*& scene = activeScene.second;
	EntityPair* pair = addEntity(scene, data);
	Entity* entity = pair->entity;
	if (entity->isAlive()) {
		initEntity(pair);
		if (entity->isAlive()) {
			delete pair;
			return entity;
		}
	}
	delete pair;
	throwError(nullptr, "La entidad no se ha instanciado correctamente");
}

void SceneManager::Init() {
	instance = std::unique_ptr<SceneManager>(new SceneManager());
	initialised = true;
}

SceneManager* SceneManager::GetInstance() {
	if (initialised) return instance.get();
	return nullptr;
}

SceneManager::~SceneManager() {

}

void SceneManager::cleanUp() {
	for (auto& scene : loadedScenes) {
		delete scene.second;
	}
	for (auto& scene : sceneBlueprints) {
		for (auto& entity : scene.second) {
			if (!entity->isBlueprint) {
				delete entity;
			}
		}
	}
	for (auto& entity : entityBlueprints) {
		delete entity.second;
	}
}

void SceneManager::setLuaState(lua_State* L) {
	lua = L;
}

lua_State* SceneManager::getLuaState() {
	return lua;
}

Entity* SceneManager::instantiateBlueprint(std::string const& bluePrintId) {
	EntityData* data = getEntityBlueprint(bluePrintId);
	return instantiateBlueprint(data);
}

Entity* SceneManager::instantiateBlueprint(std::string const& bluePrintId, forge::Vector3 const& newPos) {
	EntityData* data = getEntityBlueprint(bluePrintId);	
	auto transformData = data->components[Factory::GetInstance()->getComponentOrder(Transform::id)];
	if (transformData == nullptr) {
		throwError(nullptr, "No se ha encontrado el componente Transform en el blueprint");
	}
	transformData->add<forge::Vector3>("position", newPos);
	return instantiateBlueprint(data);
}

FORGE_API Entity* SceneManager::instantiateBlueprint(std::string const& bluePrintId, Entity* parent) {
	Entity* entity = instantiateBlueprint(bluePrintId);
	if (entity != nullptr) {
		parent->addChild(entity);
	}
	return entity;
}

bool SceneManager::changeScene(std::string const& scene, bool renewScene) {
	Scene*& activeScenePointer = activeScene.second;
	Scene* newScene;
	std::vector<Entity*> keptEntities;
	if (activeScenePointer != nullptr) {
		keptEntities = activeScenePointer->disableScene();
	}
	auto iter = loadedScenes.find(scene);
	if (iter == loadedScenes.end()) {
		newScene = createScene(scene);
	}
	else {
		if (renewScene) {
			delete iter->second;
			loadedScenes.erase(iter);
			newScene = createScene(scene);
		}
		else {
			newScene = iter->second;
			newScene->enableScene();
		}
	}
	if (newScene != nullptr) {
		for (Entity* entity : keptEntities) {
			newScene->addEntity(entity);
		}
		activeScene = { scene, newScene };
		return true;
	}
	throwError(false, "La escena no se ha encontrado o no se ha podido iniciar correctamente.");
}

void SceneManager::removeScene(std::string const& id) {
	auto iter = loadedScenes.find(id);
	if (iter != loadedScenes.end()) {
		delete iter->second;
		loadedScenes.erase(iter);
	}
}

Scene* SceneManager::createScene(std::string const& id) {
	std::unordered_set<EntityPair*> initData;
	auto iter = sceneBlueprints.find(id);
	if (iter == sceneBlueprints.end()) {
		throwError(nullptr, "Si una escena no aparece en los archivos, no existe.");
	}
	Scene* newScene = new Scene();
	for (EntityData* entityData : iter->second) {
		EntityPair* pair = addEntity(newScene, entityData);
		Entity* entity = pair->entity;
		if (!entity->isAlive()) {
			delete pair;
			reportError("No se ha podido crear la entidad.");
		}
		else {
			initData.insert(pair);
		}
	}
	for (auto& initPair : initData) {
		initEntity(initPair);
		delete initPair;
	}
	loadedScenes.insert({ id, newScene });
	newScene->refresh();
	return newScene;
}

Scene* SceneManager::getScene(std::string const& id) {
	auto iter = loadedScenes.find(id);
	if (iter != loadedScenes.end()) {
		return iter->second;
	}
	return nullptr;
}

Scene* SceneManager::getActiveScene() {
	return activeScene.second;
}

std::string const& SceneManager::getActiveSceneId() const{
	return activeScene.first;
}

int SceneManager::getMaxGroupId() {
	return static_cast<int>(groups.size());
}

bool SceneManager::update() {
	if (activeScene.second != nullptr) {
		activeScene.second->update();
		return true;
	}
	return false;
}

void SceneManager::fixedUpdate() {
	activeScene.second->fixedUpdate();
}

void SceneManager::refresh() {
	activeScene.second->refresh();
}

int SceneManager::getGroupId(std::string const& group) {
	auto iter = groups.find(group);
	if (iter == groups.end()) {
		return groups["default"];
	}
	return iter->second;
}

void SceneManager::addSceneBlueprint(std::string const& id, std::vector<EntityData*> const& scene) {
	sceneBlueprints.insert({ id,scene });
}

void SceneManager::addEntityBlueprint(std::string const& id, EntityData* entity) {
	entityBlueprints.insert({ id,entity });
}

EntityData* SceneManager::getEntityBlueprint(std::string const& id) {
	auto iter = entityBlueprints.find(id);
	if (iter == entityBlueprints.end()) {
		throwError(nullptr, "No existe el blueprint \"" << id << "\"");
	}
	return iter->second;
}


void SceneManager::addGroup(std::string const& group) {
	groups.insert({ group, getMaxGroupId()});
}
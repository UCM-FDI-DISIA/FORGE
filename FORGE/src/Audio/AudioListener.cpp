#include "AudioListener.h"
#include "Transform.h"
#include "Entity.h"
#include "AudioManager.h"
#include "ForgeError.h"

const std::string AudioListener::id = "AudioListener";

AudioListener::AudioListener() :
    transform(nullptr),
    manager(*AudioManager::GetInstance()) {
}

AudioListener::~AudioListener() {
    manager.deregisterListener(this);
}

bool AudioListener::initComponent(ComponentData* data) {
    if (!entity->hasComponent<Transform>()) {
        throwError(false, "Se necesita un componente Transform para generar un AudioListener");
    }

    if (!manager.registerListener(this)) {
        throwError(false, "Ya existia un AudioListener en la escena");
    }
    transform = entity->getComponent<Transform>();
    return true;
}

void AudioListener::update() {
    if (transform->getNeedsUpdate()) {
        manager.setListenerPosition(transform->getGlobalPosition(), transform->getForward());
    }
}
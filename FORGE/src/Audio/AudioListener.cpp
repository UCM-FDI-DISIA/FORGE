#include "AudioListener.h"
#include "Transform.h"
#include "Entity.h"
#include "AudioManager.h"

const std::string AudioListener::id = "AudioListener";

AudioListener::AudioListener() :
    transform(nullptr),
    manager(*AudioManager::getInstance()) {
}

AudioListener::~AudioListener() {
    if (isListenerActive) {
        manager.clearListenerOnScene();
    }
}

void AudioListener::initComponent(ComponentData* data) {
    transform = entity->getComponent<Transform>();
    if (manager.getListenerOnScene()) {
        entity->removeComponent(this->id);
    }
    else {
        manager.registerListenerOnScene();
        isListenerActive = true;
    }
}

void AudioListener::update() {
    if (transform->getNeedsUpdate()) {
        manager.setListenerPosition(transform->getGlobalPosition(), transform->getForward());
    }
}
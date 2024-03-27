#include "AudioListener.h"
#include "Transform.h"
#include "Entity.h"
#include "AudioManager.h"

const std::string AudioListener::id = "AudioListener";

AudioListener::AudioListener() :
    transform(nullptr),
    manager(*AudioManager::getInstance()) {
}

void AudioListener::initComponent(ComponentData* data) {
    transform = entity->getComponent<Transform>();
}

void AudioListener::update() {
    if (transform->getNeedsUpdate()) {
        manager.setListenerPosition(transform->getGlobalPosition(), transform->getForward());
    }
}
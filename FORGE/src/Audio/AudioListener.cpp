#include <iostream>
#include "AudioListener.h"
#include "Transform.h"
#include "Entity.h"
#include "AudioManager.h"

const std::string AudioListener::id = "AudioListener";

AudioListener::AudioListener() :
    transform(nullptr),
    manager(*AudioManager::GetInstance()) {
}

AudioListener::~AudioListener() {
    if (isListenerActive) {
        manager.clearListenerOnScene();
    }
}

bool AudioListener::initComponent(ComponentData* data) {
    if(entity->hasComponent<Transform>()) {
		transform = entity->getComponent<Transform>();  
	}
	else {
        std::cerr << "ERROR: Se necesita un componente Transform para inicializar el componente AudioListener\n";
		return false;
	}
    if (manager.getListenerOnScene()) {
        entity->removeComponent(this->id);
    }
    else {
        manager.registerListenerOnScene();
        isListenerActive = true;
    }
    return true;
}

void AudioListener::update() {
    if (transform->getNeedsUpdate()) {
        manager.setListenerPosition(transform->getGlobalPosition(), transform->getForward());
    }
}
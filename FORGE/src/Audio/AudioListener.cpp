#include <iostream>
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
    if (isListenerActive) {
        manager.clearListenerOnScene();
    }
}

bool AudioListener::initComponent(ComponentData* data) {
    if(entity->hasComponent<Transform>()) {
		transform = entity->getComponent<Transform>();  
	}
	else {
        throwError(false, "Se necesita un componente Transform para generar un AudioListener");
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

void AudioListener::update(double dt) {
    if (transform->getNeedsUpdate()) {
        manager.setListenerPosition(transform->getGlobalPosition(), transform->getForward());
    }
}
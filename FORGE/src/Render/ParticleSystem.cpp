#include "ParticleSystem.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"
#include "Animator.h"
#include <OgreParticleSystem.h>

const std::string ParticleSystem::id = "ParticleSystem";

ParticleSystem::ParticleSystem() :
    particle(),
    emitting(),
    ogreParticleSystem(nullptr),
    renderManager(nullptr) {
	serializer(particle, "particle");
	serializer(emitting, "emitting");
}

ParticleSystem::~ParticleSystem() {
    if(ogreParticleSystem != nullptr && renderManager != nullptr)
    {
        renderManager->removeNode(ogreParticleSystem);
    }
}

bool ParticleSystem::initComponent(ComponentData* data) {
    if(entity->hasComponent("Transform")) {
        renderManager = RenderManager::getInstance();
        ogreParticleSystem = renderManager->addParticleSystemNode(this);
    }
    else {
       		std::cerr << "ERROR: Se requiere un componente Transform para generar un ParticleSystem\n";
	}
    return ogreParticleSystem != nullptr;
}

void ParticleSystem::setEnabled(bool newActive) {
    Component::setEnabled(newActive);
    if (newActive) {
        ogreParticleSystem = renderManager->addParticleSystemNode(this);
    }
    else {
        renderManager->removeNode(ogreParticleSystem);
        ogreParticleSystem = nullptr;
    }
}

void ParticleSystem::setParticle(std::string newParticle) {
    particle = newParticle;
    renderManager->updateParticleSystemNode(ogreParticleSystem,this);
}

void ParticleSystem::setEmitting(bool newEmitting) {
    emitting = newEmitting;
    ogreParticleSystem->setEmitting(emitting);
}

const std::string& ParticleSystem::getParticle() const {
    return particle;
}

const bool& ParticleSystem::getEmitting() const {
    return emitting;
}

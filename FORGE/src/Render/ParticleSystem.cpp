#include "ParticleSystem.h"
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#include <OgreParticleSystem.h>
#pragma warning(pop)
#include "RenderManager.h"
#include "Entity.h"
#include "Serializer.h"

const std::string ParticleSystem::id = "ParticleSystem";

ParticleSystem::ParticleSystem() :
    particle(),
    emitting(),
    ogreParticleSystem(nullptr),
    renderManager(*RenderManager::GetInstance()) {
	serializer(particle, "particle");
	serializer(emitting, "emitting");
}

ParticleSystem::~ParticleSystem() {
    if(ogreParticleSystem != nullptr) {
        renderManager.removeNode(ogreParticleSystem);
    }
}

bool ParticleSystem::initComponent(ComponentData* data) {
    if (!entity->hasComponent("Transform")) {
        throwError(false, "Se requiere un componente Transform para generar un ParticleSystem");
    }
    ogreParticleSystem = renderManager.addParticleSystemNode(this);
    return true;
}

void ParticleSystem::onEnabled() {
    ogreParticleSystem = renderManager.addParticleSystemNode(this);
}

void ParticleSystem::onDisabled() {
    renderManager.removeNode(ogreParticleSystem);
    ogreParticleSystem = nullptr;
}

void ParticleSystem::setParticle(std::string const& newParticle) {
    particle = newParticle;
    renderManager.updateParticleSystemNode(ogreParticleSystem,this);
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

#include "Animator.h"
#include "Serializer.h"
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 26439)
#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#include <OgreAnimation.h>
#include <OgreEntity.h>
#pragma warning(pop)
#include "TimeForge.h"
using namespace forge;

const std::string Animator::id = "Animator";

Animator::Animator() : 
	activeAnimations(),
	ogreAnimations(nullptr) {
	serializer(activeAnimations, "activeAnimations");
}

bool Animator::initComponent(ComponentData* data) {
	if (!Mesh::initComponent(data)) {
		throwError(false, "No se ha podido inicializar el componente Animator.");
	}
	ogreAnimations = ogreEntity->getAllAnimationStates();
	if (ogreAnimations == nullptr) {
		throwError(false, "El mesh \"" << mesh << "\" no contenia animaciones.No se ha podido inicializar el componente Animator.");
		activeAnimations.clear();
	}
	for (auto it = activeAnimations.begin(); it != activeAnimations.end();) {
		if (ogreAnimations->hasAnimationState(*it)) {
			ogreAnimations->getAnimationState(*it)->setEnabled(true);
			++it;
		}
		else {
			reportError("No se ha encontrado la animacion " << *it << " en el modelo " << mesh);
			it = activeAnimations.erase(it);
		}
	}
	return true;
}

void Animator::onEnabled() {
	Mesh::onEnabled();
	ogreAnimations = ogreEntity->getAllAnimationStates();
	if (ogreAnimations == nullptr) {
		activeAnimations.clear();
		reportError("El mesh \"" << mesh << "\" no contenia animaciones.No se ha podido inicializar el componente Animator.");
	}
	for (auto it = activeAnimations.begin(); it != activeAnimations.end();) {
		if (ogreAnimations->hasAnimationState(*it)) {
			ogreAnimations->getAnimationState(*it)->setEnabled(true);
			++it;
		}
		else {
			reportError("No se ha encontrado la animacion " << *it << " en el modelo \"" << mesh << "\"");
			it = activeAnimations.erase(it);
		}
	}
}

void Animator::update() {
	for (std::string animation : activeAnimations) {
		ogreAnimations->getAnimationState(animation)->addTime(static_cast<float>(Time::deltaTime));
	}
}

std::vector<std::string> Animator::getAnimations() const {
	std::vector<std::string> animations;
	if (ogreAnimations != nullptr) {
		auto iterator = ogreAnimations->getAnimationStateIterator();
		while (iterator.hasMoreElements()) {
			animations.push_back(iterator.peekNextKey());
			iterator.moveNext();
		}
	}
	return animations;
}

std::unordered_set<std::string> const& Animator::getActiveAnimations() const {
	return activeAnimations;
}

void Animator::setLoop(std::string const& animation, bool looped) {
	if (ogreAnimations->hasAnimationState(animation)) {
		ogreAnimations->getAnimationState(animation)->setLoop(looped);
	}
}

void Animator::setActive(std::string const& animation, bool active) {
	if (ogreAnimations->hasAnimationState(animation)) {
		if (active) {
			activeAnimations.insert(animation);
		}
		else {
			activeAnimations.erase(animation);
		}
		ogreAnimations->getAnimationState(animation)->setEnabled(active);
	}
}

void Animator::setLoop(std::vector<std::string> const& animations, bool looped) {
	for (std::string const& animation : animations) {
		setLoop(animation, looped);
	}
}

void Animator::setActive(std::vector<std::string> const& animations, bool active) {
	for (std::string const& animation : animations) {
		setActive(animation, active);
	}
}

void Animator::changeActive(std::string const& newAnimation) {
	for (std::string const& animation : activeAnimations) {
		ogreAnimations->getAnimationState(animation)->setEnabled(false);
	}
	activeAnimations.clear();
	setActive(newAnimation, true);
}

void Animator::changeActive(std::vector<std::string> const& newAnimations) {
	for (std::string const& animation : activeAnimations) {
		setActive(animation, false);
	}
	setActive(newAnimations, true);
}
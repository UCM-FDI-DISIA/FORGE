#include "Animator.h"
#include "Serializer.h"
#include "Entity.h"
#include "OgreAnimation.h"
#include "OgreEntity.h"

const std::string Animator::id = "Animator";

Animator::Animator() : 
	activeAnimations(),
	ogreAnimations(nullptr) {
	serializer(mesh, "mesh");
	serializer(material, "material");
	serializer(activeAnimations, "activeAnimations");
}

Animator::~Animator() {}

bool Animator::initComponent(ComponentData* data) {
	if(Mesh::initComponent(data)){
		ogreAnimations = ogreEntity->getAllAnimationStates();
		if (ogreAnimations != nullptr) {
			for (auto it = activeAnimations.begin(); it != activeAnimations.end();) {
				if (ogreAnimations->hasAnimationState(*it)) {
					ogreAnimations->getAnimationState(*it)->setEnabled(true);
					++it;
				}
				else {
					it = activeAnimations.erase(it);
				}
			}
			return true;
		}
		activeAnimations.clear();
		std::cerr << "ERROR: No se ha podido inicializar el componente Animator\n";
		return false;
	}
	std::cerr << "ERROR: No se ha podido inicializar el componente Mesh\n";
	return false;
}

void Animator::update() {
	for (std::string animation : activeAnimations) {
		ogreAnimations->getAnimationState(animation)->addTime(0.017f /*TODO: DELTA TIME*/);
	}
}

void Animator::setLoop(std::string animation, bool looped) {
	if (ogreAnimations->hasAnimationState(animation)) {
		ogreAnimations->getAnimationState(animation)->setLoop(looped);
	}
}

void Animator::setActive(std::string animation, bool active) {
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

void Animator::setLoop(std::vector<std::string> animations, bool looped) {
	for (std::string animation : animations) {
		setLoop(animation, looped);
	}
}

void Animator::setActive(std::vector<std::string> animations, bool active) {
	for (std::string animation : animations) {
		setActive(animation, active);
	}
}

void Animator::changeActive(std::string newAnimation) {
	for (std::string animation : activeAnimations) {
		ogreAnimations->getAnimationState(animation)->setEnabled(false);
	}
	activeAnimations.clear();
	setActive(newAnimation, true);
}

void Animator::changeActive(std::vector<std::string> newAnimations) {
	for (std::string animation : activeAnimations) {
		setActive(animation, false);
	}
	setActive(newAnimations, true);
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

const std::unordered_set<std::string>& Animator::getActiveAnimations() const {
	return activeAnimations;
}


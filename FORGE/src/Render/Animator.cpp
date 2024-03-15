#include "Animator.h"
#include "OgreAnimation.h"
#include "Serializer.h"
#include "Entity.h"

const std::string Animator::id = "Animator";

Animator::Animator() : 
	activeAnimations(),
	ogreAnimations(nullptr),
	renderManager(nullptr) {
	serializer(activeAnimations, "activeAnimations");
}

Animator::~Animator() {}

void Animator::init(RenderManager* manager, Ogre::AnimationStateSet* animationSet) {
	renderManager = manager;
	ogreAnimations = animationSet;
	for (auto it = activeAnimations.begin(); it != activeAnimations.end();) {
		if (ogreAnimations->hasAnimationState(*it)) {
			ogreAnimations->getAnimationState(*it)->setEnabled(true);
			++it;
		}
		else { 
			it = activeAnimations.erase(it);
		}
	}
}

void Animator::update() {
	if(ogreAnimations == nullptr){
		entity->removeComponent("Animator");
	}
	else {
		//auto map = ogreAnimations->getAnimationStates();
		for (std::string animation : activeAnimations) {
			ogreAnimations->getAnimationState(animation)->addTime(0.017f /*TODO: DELTA TIME*/);
		}
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
		setActive(animation, false);
	}
	setActive(newAnimation, true);
}

void Animator::changeActive(std::vector<std::string> newAnimations) {
	for (std::string animation : activeAnimations) {
		setActive(animation, false);
	}
	setActive(newAnimations, true);
}

Ogre::AnimationStateSet* Animator::getAnimations() {
	return ogreAnimations;
}

std::unordered_set<std::string> Animator::getActiveAnimations() {
	return activeAnimations;
}

#include "TimeForge.h"

double forge::Time::_deltaTime = 0.0;
std::unique_ptr<forge::Time> forge::Time::instance = nullptr;

forge::Time::Time() :
	previous(time(NULL)) {
}

forge::Time* forge::Time::getInstance() {
	if (instance != nullptr) return instance.get();
	return (instance = std::unique_ptr<forge::Time>(new forge::Time())).get();
}

void forge::Time::init() noexcept {
	time(&previous);
}

void forge::Time::update() noexcept {
	time_t current = time(NULL);
	_deltaTime = difftime(current, previous);
	previous = current;
}
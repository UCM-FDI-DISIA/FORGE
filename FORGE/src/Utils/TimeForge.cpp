#include "TimeForge.h"

std::unique_ptr<forge::Time> forge::Time::instance = nullptr;

forge::Time::Time() :
	previous(::time(NULL)) {
	_deltaTime = 0.0;
}

forge::Time* forge::Time::getInstance() {
	if (instance != nullptr) return instance.get();
	return (instance = std::unique_ptr<forge::Time>(new forge::Time())).get();
}

void forge::Time::initDT() noexcept {
	::time(&previous);
}

void forge::Time::updateDT() noexcept {
	time_t current = ::time(NULL);
	_deltaTime = ::difftime(current, previous);
	previous = current;
}
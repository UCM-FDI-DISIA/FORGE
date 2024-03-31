#include "Time.h"

std::unique_ptr<Time> Time::instance = nullptr;

Time::Time() {
	_deltaTime = 0.0;
}

Time* Time::getInstance() {
	if (instance != nullptr) return instance.get();
	return (instance = std::unique_ptr<Time>(new Time())).get();
}

void Time::initDT() noexcept {
	time(&previous);
}

void Time::updateDT() noexcept {
	time_t current = time(nullptr);
	_deltaTime = difftime(current, previous);
	previous = current;
}
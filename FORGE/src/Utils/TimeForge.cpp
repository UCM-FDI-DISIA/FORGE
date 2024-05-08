#include "TimeForge.h"

double forge::Time::_deltaTime = 0.0;
double forge::Time::_time = 0.0;
std::unique_ptr<forge::Time> forge::Time::instance = nullptr;

forge::Time::Time() :
	previous() {
}

forge::Time* forge::Time::GetInstance() {
	if (instance != nullptr) return instance.get();
	return (instance = std::unique_ptr<forge::Time>(new forge::Time())).get();
}

void forge::Time::init() noexcept {
	previous = std::chrono::system_clock::now();
}

void forge::Time::update() noexcept {	
	std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
	_deltaTime = std::chrono::duration<double>(current - previous).count();
	_time += _deltaTime;
	previous = current;
}
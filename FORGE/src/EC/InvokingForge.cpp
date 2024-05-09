#include "InvokingForge.h"
#include "Invoker.h"

std::unique_ptr<InvokingForge> InvokingForge::instance = nullptr;
bool InvokingForge::initialised = false;

InvokingForge::InvokingForge() : 
	invokerContainers() {
}

bool InvokingForge::Init() {
	if (!initialised) {
		instance = std::unique_ptr<InvokingForge>(new InvokingForge());
		initialised = true;
		return true;
	}
	return false;
}

InvokingForge* InvokingForge::GetInstance() {
	if (initialised) {
		return instance.get();
	}
	return nullptr;
}

void InvokingForge::shutDown() {
	for (auto& container : invokerContainers) {
		container.clear();
	}
	for (auto& invoker : invokers) {
		delete invoker;
	}
	invokers.clear();
}

Invoker& InvokingForge::generate() {
	invokers.push_back(new Invoker());
	return *invokers.back();
}

std::unordered_map<std::string, std::function<void()>>& InvokingForge::registerInvoker() {
	invokerContainers.push_back({});
	return invokerContainers.back();
}


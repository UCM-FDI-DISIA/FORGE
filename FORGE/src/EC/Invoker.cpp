#include "Invoker.h"
#include "InvokingForge.h"

Invoker::Invoker() :
	valid(false),
	functions(InvokingForge::GetInstance()->registerInvoker()) {
}

void Invoker::registerFunction(std::string const& name, std::function<void()> const& f) {
	functions.insert(std::pair<std::string, std::function<void()>>(name, f));
}

void Invoker::invoke(std::string const& func) {
	if (valid) {
		auto it = functions.find(func);
		if (it != functions.end()) {
			it->second();
		}
	}
}

void Invoker::invalidate() {
	valid = false;
}
#include "Invoker.h"
#include "InvokingForge.h"

Invoker::Invoker() :
	functions(InvokingForge::GetInstance()->registerInvoker()) {
}

void Invoker::registerFunction(std::string const& name, std::function<void()> const& f) {
	functions.insert(std::pair<std::string, std::function<void()>>(name, f));
}

void Invoker::invoke(std::string const& func) {
	auto it = functions.find(func);
	if (it != functions.end()) {
		it->second();
	}
}
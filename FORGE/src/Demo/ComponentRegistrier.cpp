#include "Factory.h"
#include "TestMovement.h"
#define FORGE_IMPORT extern "C" __declspec(dllexport)
FORGE_IMPORT void registerComponents(Factory& f) {
	f.registerComponent<TestMovement>();
}
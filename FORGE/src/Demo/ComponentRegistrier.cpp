#include "Factory.h"
#include "TestComponent.h"
#include "ForgeImport.h"
FORGE_IMPORT void registerComponents(Factory& f) {
	f.registerComponent<TestComponent>();
}
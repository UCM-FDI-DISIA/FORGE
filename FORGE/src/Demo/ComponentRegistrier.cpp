#include "Factory.h"
#include "TestMovement.h"
#include "ForgeImport.h"
FORGE_IMPORT void registerComponents(Factory& f) {
	f.registerComponent<TestMovement>();
}
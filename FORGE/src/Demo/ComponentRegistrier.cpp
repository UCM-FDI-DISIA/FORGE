#include "Factory.h"
#include "TestMovement.h"
extern "C" {
	__declspec(dllexport) void registerComponents(Factory& f) {
		f.registerComponent<TestMovement>();
	}
}

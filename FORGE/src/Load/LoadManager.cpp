#include "LoadManager.h"
#include "LuaForge.h"
#include "EcsLoad.h"
#include "AudioLoad.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)

LoadManager::LoadManager(std::string const& assetsFile, std::string const& scenesFile) : 
	luaForge(new LuaForge()) {
	if (!luaForge->doFile(assetsFile)) {
		luabridge::LuaRef audioRef = luabridge::getGlobal(luaForge->getState(), "Audio");
		if (!audioRef.isNil()) {
			AudioLoad::AudioLoad(audioRef);
		}

		EcsLoad(scenesFile, *luaForge);
	}
}

LoadManager::~LoadManager() {
	delete luaForge;
}

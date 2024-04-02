#include "AudioLoad.h"
#include <lua.hpp>
#pragma warning(push)
#pragma warning(disable : 26439)
#include <LuaBridge/LuaBridge.h>
#pragma warning(pop)
#include "AudioManager.h"
AudioLoad::AudioLoad(luabridge::LuaRef& audioRef) {
	AudioManager& am = *AudioManager::getInstance();
	for (auto&& audio : pairs(audioRef)) {
		if (audio.second.isTable()) {
			auto path = audio.second["path"];
			if (!path.isNil()) {
				am.addSound(audio.first.cast<std::string>(), path.cast<std::string>());
			}
		}
	}
}
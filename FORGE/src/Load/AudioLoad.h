#pragma once
#ifndef AUDIO_LOAD_H_
#define AUDIO_LOAD_H_
namespace luabridge {
	class LuaRef;
}
class AudioLoad {
public:
	AudioLoad(luabridge::LuaRef& audioRef);
};
#endif // !AUDIO_LOAD_H_

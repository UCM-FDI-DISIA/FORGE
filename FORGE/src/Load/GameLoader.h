#ifndef GAME_LOADER_H_
#define GAME_LOADER_H_
#include <string>
#include <Windows.h>
class Factory;

class GameLoader {
private:
	// Handle to DLL
	HINSTANCE hDLL;
public:
	GameLoader();
	bool init(std::string const& gameDll);
	bool registerComponents(Factory& f);
	bool free();
};

#endif // !GAME_LOADER_H_
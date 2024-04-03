#ifndef GAME_LOAD_H_
#define GAME_LOAD_H_
#include <string>
#include <Windows.h>
class Factory;

class GameLoad {
private:
	// Handle to DLL
	HINSTANCE hDLL;
public:
	GameLoad();
	bool init(std::string const& gameDll);
	bool registerComponents(Factory& f);
	bool free();
};

#endif // !GAME_LOAD_H_
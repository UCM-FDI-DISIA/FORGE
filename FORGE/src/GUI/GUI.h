#pragma once

#include <memory>

class GUI {
private:

public:
	static std::unique_ptr<GUI> instance;

	//GUI();

	//~GUI();

	void createText();

};
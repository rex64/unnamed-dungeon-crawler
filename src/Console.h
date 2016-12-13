#pragma once
#include <string>

class Console
{
public:
	Console();
	~Console();
	void init();

	//IInputReceiver
	//bool onInput(SDL_Event* e);

	static Console* console;

	bool visible;
	bool showCursor;
	std::string cmd;
	std::string buff;
};

#pragma once
#include <string>
#include "IInputReceiver.h"
class Console : public IInputReceiver
{
public:
	Console();
	~Console();
	void init();

	//IInputReceiver
	bool onInput(SDL_Event* e);

	static Console* console;

	bool visible;
	bool showCursor;
	std::string cmd;
	std::string buff;
};

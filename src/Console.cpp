#include "Console.h"

Console* Console::console;

Console::Console() : visible(false), cmd(""), buff(""), showCursor(false)
{
}

Console::~Console()
{
}

void Console::init() {
	console = this;
}

bool Console::onInput(SDL_Event* e) {

	return true;
}

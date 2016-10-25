#include "Console.h"

Console* Console::console;

Console::Console() : visible(false), cmd(""), buff("")
{
}

Console::~Console()
{
}

void Console::init() {
	console = this;
}

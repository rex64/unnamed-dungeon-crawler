#include "Console.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "ScriptManager.h"

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

//bool Console::onInput(SDL_Event* e) {
//
//	if (!visible) {
//		return false;
//	}
//
//	if (Console::console->visible == true) {
//
//		if (e->key.keysym.sym == SDLK_BACKSPACE) {
//			Console::console->cmd = Console::console->cmd.substr(0, Console::console->cmd.length() - 1);
//		}
//		else if (e->type == SDL_TEXTINPUT) {
//			Console::console->cmd = Console::console->cmd + e->text.text;
//		}
//		else if (e->key.keysym.sym == SDLK_RETURN) {
//			ScriptManager::manager->doString(Console::console->cmd.c_str());
//			Console::console->cmd = "";
//
//		}
//	}
//
//	return true;
//}

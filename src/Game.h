#pragma once

#ifdef __APPLE__
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#elif _WIN32
#include <lua.hpp>
#endif

#include <string>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 225

#define GAME_WIDTH 256
#define GAME_HEIGHT 144

struct SDL_Window;

struct Buttons {

	bool up;
	bool right;
	bool down;
	bool left;

	bool ok;
	bool cancel;

	bool menu;
};

class Game
{
public:
	Game();
	~Game();

	void init();
	void run();

	void showMsgBox(std::string msg);
	void showMsgBox(const char *msg);
	void quit();

public:
	static Game *game;
	SDL_Window *window;
	bool inputEnabled;
private:
	bool m_bQuit;
};

extern "C" {

	int Game_enableInput(lua_State *L);
	int Game_disableInput(lua_State *L);

}

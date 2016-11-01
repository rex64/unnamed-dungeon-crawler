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

#include "IInputReceiver.h"

class ScriptManager : public IInputReceiver
{
public:
	ScriptManager();
	~ScriptManager();

	void init();
	void runMain();
	void doString(const char *str);

	static ScriptManager *manager;

	bool onInput(SDL_Event* e);

private:
	lua_State *m_L;
};

extern "C" static void stackDump(lua_State *L);
extern "C" static int luaTestFunc(lua_State* state);
extern "C" static int luaQuitGame(lua_State* state);
extern "C" static int l_setTile(lua_State* state);

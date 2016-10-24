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

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void init();
	void doString(const char *str);

	static ScriptManager *manager;

private:
	lua_State *m_L;
};

extern "C" static void stackDump(lua_State *L);
extern "C" static int luaTestFunc(lua_State* state);
extern "C" static int luaQuitGame(lua_State* state);
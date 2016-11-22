#include <stdio.h>

#ifdef __APPLE__
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#elif _WIN32
#include <lua.hpp>
#endif

extern "C" {

	
	int luaopen_Windowlib(lua_State *L);
	void check_Window(lua_State *L, int i);
	int WindowLib_new(lua_State *L);
	int Window__gc(lua_State *L);
	int Window_method(lua_State *L);
	int Window_addMenuItem(lua_State *L);

}
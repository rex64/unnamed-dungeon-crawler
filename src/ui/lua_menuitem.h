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

	
	int luaopen_MenuItemLib(lua_State *L);
	void check_MenuItem(lua_State *L, int i);
	int MenuItem_new(lua_State *L);
	int MenuItem__newindex(lua_State *L);
	int MenuItem__index(lua_State *L);
	int MenuItem__gc(lua_State *L);
	//int MenuItem_method(lua_State *L);
	int MenuItem_onSelect(lua_State *L);

}

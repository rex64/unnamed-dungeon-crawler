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
	
	
	//int luaopen_Menulib(lua_State *L);
	int Menu_renderWindow(lua_State *L);
	int Menu_renderMenuItem(lua_State *L);
	int Menu_renderSprite(lua_State *L);
	/*void check_Menu(lua_State *L, int i);
	int Menu_new(lua_State *L);
	int Menu__gc(lua_State *L);
	int Menu__newindex(lua_State *L);
	int Menu__index(lua_State *L);*/

}

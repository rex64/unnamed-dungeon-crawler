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
	void check_Obj(lua_State *L, int i);
	int MyLib_MakeObj(lua_State *L);
	int Obj__gc(lua_State *L);
	int Obj_method(lua_State *L);

}
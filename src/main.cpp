#ifdef __APPLE__

    #include <SDL2/SDL.h>

    extern "C" {
        #include <lua.h>
        #include <lualib.h>
        #include <lauxlib.h>
    }

#elif _WIN32

    #define SDL_MAIN_HANDLED
    #include <SDL.h>
    #include <stdio.h>
    #include <lua.hpp>

#endif

#include <iostream>
#include "Game.h"
/*
const static char *Obj_typename = "ObjTypename";

void check_Obj(lua_State *L, int i) {
	luaL_checkudata(L, i, Obj_typename);
}

int MyLib_MakeObj(lua_State *L) {
	printf("In MyLib_MakeObj\n");
	lua_newuserdata(L, sizeof(int*));
	luaL_setmetatable(L, Obj_typename);
	return 1;
}
int Obj__gc(lua_State *L) {
	printf("In Obj__gc\n");
	return 0;
}
int Obj_method(lua_State *L) {
	printf("In Obj_method\n");
	check_Obj(L, 1);
	return 0;
}

int luaopen_MyLib(lua_State *L) {
	static const luaL_Reg Obj_lib[] = {
		{ "method", &Obj_method },
		{ NULL, NULL }
	};

	static const luaL_Reg MyLib_lib[] = {
		{ "MakeObj", &MyLib_MakeObj },
		{ NULL, NULL }
	};

	luaL_newlib(L, MyLib_lib);

	// Stack: MyLib
	luaL_newmetatable(L, Obj_typename); // Stack: MyLib meta
	luaL_newlib(L, Obj_lib);
	lua_setfield(L, -2, "__index"); // Stack: MyLib meta

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, Obj__gc); // Stack: MyLib meta "__gc" fptr
	lua_settable(L, -3); // Stack: MyLib meta
	lua_pop(L, 1); // Stack: MyLib

	return 1;
}
*/

int main(int argc, char* argv[]) {

	Game *g = new Game();
	g->init();
	/*
	int iarg;
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	luaL_requiref(L, "MyLib", luaopen_MyLib, 1);

	if (luaL_dofile(L, "data/base/scripts/test.lua")) {
		std::cout << lua_tostring(L, -1);
	}

	lua_close(L);
	std::cout << "CIAO\n";
	*/
	g->run();

    return 0;

}

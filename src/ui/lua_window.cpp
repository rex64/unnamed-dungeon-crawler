#include "lua_window.h"
#include <stdio.h>
#include "../ScriptManager.h"
#include "MenuManager.h"

const static char *Obj_typename = "Window";

int luaopen_Windowlib(lua_State *L)
{

	//stackDump(L);

	static const luaL_Reg Window_lib[] = {
		{ "method", &Window_method },
		{ NULL, NULL }
	};

	static const luaL_Reg WindowLib_lib[] = {
		{ "new", &WindowLib_new },
		{ NULL, NULL }
	};

	luaL_newlib(L, WindowLib_lib);

	// Stack: MyLib
	luaL_newmetatable(L, Obj_typename); // Stack: MyLib meta
	luaL_newlib(L, Window_lib);
	lua_setfield(L, -2, "__index"); // Stack: MyLib meta

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, Window__gc); // Stack: MyLib meta "__gc" fptr
	lua_settable(L, -3); // Stack: MyLib meta
	lua_pop(L, 1); // Stack: MyLib

	return 1;
}

void check_Window(lua_State *L, int i) {
	luaL_checkudata(L, i, Obj_typename);
}

int WindowLib_new(lua_State *L) {

	//1  This function allocates a new block of memory with the given size, 
	//   pushes onto the stack a new full userdata with the block address, 
	//   and returns this address. The host program can freely use this memory.
	/*lua_newuserdata(L, sizeof(int*));
	luaL_setmetatable(L, Obj_typename);*/
	
	int x = lua_tointeger(L, 1);
	int y = lua_tointeger(L, 2);

	Window **pWindow = reinterpret_cast<Window **>(lua_newuserdata(L, sizeof(Window*)));
	*pWindow = new Window(x, y);

	luaL_setmetatable(L, Obj_typename);

	return 1;
}
int Window__gc(lua_State *L) {
	printf("In Window__gc\n");

	Window **pWindow = reinterpret_cast<Window **>(lua_touserdata(L, 1));
	delete *pWindow;

	return 0;
}
int Window_method(lua_State *L) {
	//stackDump(L);
	printf("In Window_method\n");
	check_Window(L, 1);
	return 0;
}
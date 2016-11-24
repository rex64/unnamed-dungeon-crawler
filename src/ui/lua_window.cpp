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
		{ "addMenuItem", &Window_addMenuItem },
		{ "getMenuItem", &Window_getMenuItem },
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

int Window_addMenuItem(lua_State * L)
{
	//stolen from: http://stackoverflow.com/questions/18478379/how-to-work-with-tables-passed-as-an-argument-to-a-lua-c-function
	// discard any extra arguments passed in
	//stackDump(L);
	//lua_settop(L, 2);
	//stackDump(L);
	
	/*
	luaL_checktype(L, 2, LUA_TTABLE);

	// Now to get the data out of the table
	// 'unpack' the table by putting the values onto
	// the stack first. Then convert those stack values
	// into an appropriate C type.
	lua_getfield(L, 2, "text");
	lua_getfield(L, 2, "x");
	lua_getfield(L, 2, "y");
	*/
	stackDump(L);

	const char *text = luaL_checkstring(L, -4);
	int x = luaL_checkinteger(L, -3);
	int y = luaL_checkinteger(L, -2);
	int callbackFuncRef = luaL_ref(L, LUA_REGISTRYINDEX);

	stackDump(L);

	Window **pWindow = reinterpret_cast<Window **>(lua_touserdata(L, 1));
	(*pWindow)->addMenuItem(new MenuItem(text, x, y, callbackFuncRef));

	lua_pop(L, 3);

	return 0;
}

int Window_getMenuItem(lua_State * L)
{
	
	Window **pWindow = reinterpret_cast<Window **>(lua_touserdata(L, 1));
	
	int index = luaL_checkinteger(L, 2);
	
	MenuItem *menuItem = (*pWindow)->menuItems[index];

	


	return 1;
}

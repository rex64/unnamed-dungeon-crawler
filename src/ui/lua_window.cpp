#include "lua_window.h"
#include <stdio.h>
#include "../ScriptManager.h"
#include "MenuManager.h"

const static char *Obj_typename = "Window";

int luaopen_Windowlib(lua_State *L)
{

	//stackDump(L);

	/*static const luaL_Reg Window_lib[] = {
		{ "method", &Window_method },
		{ "addMenuItem", &Window_addMenuItem },
		{ "getMenuItem", &Window_getMenuItem },
		{ "new", &WindowLib_new },
		{ "__newindex", &Window__newindex },
		{ NULL, NULL }
	};*/

	// Stack: MyLib
	luaL_newmetatable(L, Obj_typename); // Stack: MyLib meta
	stackDump(L);

	lua_pushstring(L, "new");
	lua_pushcfunction(L, WindowLib_new);
	lua_settable(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, Window__newindex);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcfunction(L, Window__index);
	lua_settable(L, -3);

	stackDump(L);
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

	stackDump(L);

	//Pops a table from the stack and 
	//sets it as the new metatable for 
	//the value at the given index.
	luaL_setmetatable(L, Obj_typename); 


	stackDump(L);

	lua_newtable(L);
	stackDump(L);
	lua_setuservalue(L, -2);

	stackDump(L);
	return 1;
}
int Window__gc(lua_State *L) {
	printf("In Window__gc\n");

	Window **pWindow = reinterpret_cast<Window **>(lua_touserdata(L, 1));
	delete *pWindow;

	return 0;
}

int Window__newindex(lua_State *L) {
	printf("In Window__newindex\n");

	return 0;
}

int Window__index(lua_State *L) {
	printf("In Window__index\n");

	lua_pushnumber(L, 10);

	return 1;
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

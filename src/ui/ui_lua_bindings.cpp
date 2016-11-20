#include "ui_lua_bindings.h"
#include <stdio.h>
#include "../ScriptManager.h"
#include "MenuManager.h"

const static char *Obj_typename = "ObjTypename";

int luaopen_Windowlib(lua_State *L)
{

	stackDump(L);

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

void check_Obj(lua_State *L, int i) {
	luaL_checkudata(L, i, Obj_typename);
}

int MyLib_MakeObj(lua_State *L) {

	//1  This function allocates a new block of memory with the given size, 
	//   pushes onto the stack a new full userdata with the block address, 
	//   and returns this address. The host program can freely use this memory.
	/*lua_newuserdata(L, sizeof(int*));
	luaL_setmetatable(L, Obj_typename);*/
	
	Window **pWindow = reinterpret_cast<Window **>(lua_newuserdata(L, sizeof(Window*)));
	*pWindow = new Window();


	return 1;
}
int Obj__gc(lua_State *L) {
	printf("In Obj__gc\n");

	Window **pWindow = reinterpret_cast<Window **>(lua_touserdata(L, 1));
	delete *pWindow;

	return 0;
}
int Obj_method(lua_State *L) {
	//stackDump(L);
	printf("In Obj_method\n");
	check_Obj(L, 1);
	return 0;
}
#include "lua_menuitem.h"
#include <stdio.h>
#include "../ScriptManager.h"
#include "MenuManager.h"

const static char *Obj_typename = "MenuItem";

int luaopen_MenuItemLib(lua_State *L)
{

	//stackDump(L);

	static const luaL_Reg MenuItem_lib[] = {
		/*{ "method", &MenuItem_method },
		{ "addMenuItem", &MenuItem_addMenuItem },*/
		{ "onSelect", &MenuItem_onSelect },
		{ NULL, NULL }
	};

	static const luaL_Reg MenuItemLib_lib[] = {
		{ "new", &MenuItemLib_new },
		{ NULL, NULL }
	};

	luaL_newlib(L, MenuItemLib_lib);

	// Stack: MyLib
	luaL_newmetatable(L, Obj_typename); // Stack: MyLib meta
	luaL_newlib(L, MenuItem_lib);
	lua_setfield(L, -2, "__index"); // Stack: MyLib meta

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, MenuItem__gc); // Stack: MyLib meta "__gc" fptr
	lua_settable(L, -3); // Stack: MyLib meta
	lua_pop(L, 1); // Stack: MyLib

	return 1;
}

void check_MenuItem(lua_State *L, int i) {
	luaL_checkudata(L, i, Obj_typename);
}

int MenuItemLib_new(lua_State *L) {
	
	std::string s = lua_tostring(L, 1);
	int x = lua_tointeger(L, 2);
	int y = lua_tointeger(L, 3);
	int callbackFuncRef = luaL_ref(L, LUA_REGISTRYINDEX);


	MenuItem **pMenuItem = reinterpret_cast<MenuItem **>(lua_newuserdata(L, sizeof(MenuItem*)));
	*pMenuItem = new MenuItem(s, x, y, callbackFuncRef);

	luaL_setmetatable(L, Obj_typename);

	return 1;
}
int MenuItem__gc(lua_State *L) {
	printf("In MenuItem__gc\n");

	/*Window **pWindow = reinterpret_cast<Window **>(lua_touserdata(L, 1));
	delete *pWindow;*/

	return 0;
}
int MenuItem_method(lua_State *L) {
	//stackDump(L);
	printf("In MenuItem_method\n");
	check_MenuItem(L, 1);
	return 0;
}

int MenuItem_onSelect(lua_State *L) {

	stackDump(L);

	MenuItem **pMenuItem = reinterpret_cast<MenuItem **>(lua_touserdata(L, 1));

	/* push the callback onto the stack using the Lua reference we */
	/*  stored in the registry */
	lua_rawgeti(L, LUA_REGISTRYINDEX, (*pMenuItem)->callbackRef);

	stackDump(L);

	/* duplicate the value on the stack */
	/* NOTE: This is unnecessary, but it shows how you keep the */
	/*  callback for later */
	lua_pushvalue(L, -1);

	stackDump(L);

	/* call the callback */
	/* NOTE: This is using the one we duplicated with lua_pushvalue */
	if (0 != lua_pcall(L, 0, 0, 0)) {
		printf("Failed to call the callback!\n %s\n", lua_tostring(L, -1));
		//return;
	}

	/* get a new reference to the Lua function and store it again */
	/* NOTE: This is only used in conjunction with the lua_pushvalue */
	/*  above and can be removed if you remove that */
	(*pMenuItem)->callbackRef = luaL_ref(L, LUA_REGISTRYINDEX);

	return 0;

}
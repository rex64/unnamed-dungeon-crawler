#include "lua_menuitem.h"
#include <stdio.h>
#include "../ScriptManager.h"
#include "MenuManager.h"

const static char *Obj_typename = "MenuItem";

int luaopen_MenuItemLib(lua_State *L)
{

	luaL_newmetatable(L, Obj_typename);

	lua_pushstring(L, "new");
	lua_pushcfunction(L, MenuItem_new);
	lua_settable(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, MenuItem__newindex);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcfunction(L, MenuItem__index);
	lua_settable(L, -3);

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, MenuItem__gc);
	lua_settable(L, -3);

	return 1;
}

void check_MenuItem(lua_State *L, int i) {
	luaL_checkudata(L, i, Obj_typename);
}

int MenuItem_new(lua_State *L) {
	
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
//int MenuItem_method(lua_State *L) {
//	//stackDump(L);
//	printf("In MenuItem_method\n");
//	check_MenuItem(L, 1);
//	return 0;
//}

int MenuItem__newindex(lua_State *L) { //userdata key (new)value
	printf("In Window__newindex\n");


	lua_getuservalue(L, 1); //1 userdata


	lua_pushvalue(L, 2);
	lua_pushvalue(L, 3);

	lua_rawset(L, 4);


	return 0;
}

int MenuItem__index(lua_State *L) { //userdata key
	printf("In Window__index\n");


	lua_getuservalue(L, 1); //1 userdata
	lua_pushvalue(L, 2);

	lua_rawget(L, 3);


	return 1;
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
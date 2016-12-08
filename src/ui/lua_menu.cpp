#include "lua_menu.h"
#include <stdio.h>
#include "../ScriptManager.h"
#include "MenuManager.h"
#include "../RenderManager.h"

const static char *Obj_typename = "Menu";

//int luaopen_Menulib(lua_State *L)
//{
//
//	//stackDump(L);
//
//	/*static const luaL_Reg Window_lib[] = {
//		{ "method", &Window_method },
//		{ "addMenuItem", &Window_addMenuItem },
//		{ "getMenuItem", &Window_getMenuItem },
//		{ "new", &WindowLib_new },
//		{ "__newindex", &Window__newindex },
//		{ NULL, NULL }
//	};*/
//
//	// Stack: MyLib
//	luaL_newmetatable(L, Obj_typename); // Stack: MyLib meta
//	stackDump(L);
//
//	/*lua_pushstring(L, "new");
//	lua_pushcfunction(L, Menu_new);
//	lua_settable(L, -3);
//
//	lua_pushstring(L, "__newindex");
//	lua_pushcfunction(L, Menu__newindex);
//	lua_settable(L, -3);
//
//	lua_pushstring(L, "__index");
//	lua_pushcfunction(L, Menu__index);
//	lua_settable(L, -3);
//
//	lua_pushstring(L, "__gc");
//	lua_pushcfunction(L, Menu__gc);
//	lua_settable(L, -3);*/
//
//	stackDump(L);
//	return 1;
//}

int Menu_renderWindow(lua_State *L) {

	int x = lua_tointeger(L, 1);
	int y = lua_tointeger(L, 2);
	int h = lua_tointeger(L, 3);
	int w = lua_tointeger(L, 4);


	SDL_Rect rect = {x, y, h, w};
	RenderManager::manager->renderWindow(rect);

	return 0;
}

int Menu_renderMenuItem(lua_State *L) {

	std::string text = lua_tostring(L, 1);
	int x = lua_tointeger(L, 2);
	int y = lua_tointeger(L, 3);

	RenderManager::manager->renderMenuItem(text, x, y);

	return 0;
}

int Menu_renderSprite(lua_State *L) {

	std::string text = lua_tostring(L, 1);
	int x = lua_tointeger(L, 2);
	int y = lua_tointeger(L, 3);

	RenderManager::manager->renderSprite(text, x, y);

	return 0;
}

//void check_Menu(lua_State *L, int i) {
//	luaL_checkudata(L, i, Obj_typename);
//}
//
//int Menu_new(lua_State *L) {
//
//	//1  This function allocates a new block of memory with the given size, 
//	//   pushes onto the stack a new full userdata with the block address, 
//	//   and returns this address. The host program can freely use this memory.
//	/*lua_newuserdata(L, sizeof(int*));
//	luaL_setmetatable(L, Obj_typename);*/
//	
//	int x = lua_tointeger(L, 1);
//	int y = lua_tointeger(L, 2);
//
//	Window **pWindow = reinterpret_cast<Window **>(lua_newuserdata(L, sizeof(Window*)));
//	*pWindow = new Window(x, y);
//
//	
//
//	//Pops a table from the stack and 
//	//sets it as the new metatable for 
//	//the value at the given index.
//	luaL_setmetatable(L, Obj_typename); 
//
//
//	
//
//	lua_newtable(L);
//	
//	lua_setuservalue(L, -2);
//
//	
//	return 1;
//}
//int Window__gc(lua_State *L) {
//	printf("In Window__gc\n");
//
//	Window **pWindow = reinterpret_cast<Window **>(lua_touserdata(L, 1));
//	delete *pWindow;
//
//	return 0;
//}
//
//int Window__newindex(lua_State *L) { //userdata key (new)value
//	printf("In Window__newindex\n");
//	
//
//	lua_getuservalue(L, 1); //1 userdata
//
//
//	lua_pushvalue(L, 2);
//	lua_pushvalue(L, 3);
//
//	lua_rawset(L, 4);
//
//
//	return 0;
//}
//
//int Window__index(lua_State *L) { //userdata key
//	printf("In Window__index\n");
//
//
//	lua_getuservalue(L, 1); //1 userdata
//	lua_pushvalue(L, 2);
//
//	lua_rawget(L, 3);
//	
//
//	return 1;
//}


//int Window_method(lua_State *L) {
//	//stackDump(L);
//	printf("In Window_method\n");
//	check_Window(L, 1);
//	return 0;
//}

//int Window_addMenuItem(lua_State * L)
//{
//	//stolen from: http://stackoverflow.com/questions/18478379/how-to-work-with-tables-passed-as-an-argument-to-a-lua-c-function
//	// discard any extra arguments passed in
//	//stackDump(L);
//	//lua_settop(L, 2);
//	//stackDump(L);
//	
//	/*
//	luaL_checktype(L, 2, LUA_TTABLE);
//
//	// Now to get the data out of the table
//	// 'unpack' the table by putting the values onto
//	// the stack first. Then convert those stack values
//	// into an appropriate C type.
//	lua_getfield(L, 2, "text");
//	lua_getfield(L, 2, "x");
//	lua_getfield(L, 2, "y");
//	*/
//	stackDump(L);
//
//	const char *text = luaL_checkstring(L, -4);
//	int x = luaL_checkinteger(L, -3);
//	int y = luaL_checkinteger(L, -2);
//	int callbackFuncRef = luaL_ref(L, LUA_REGISTRYINDEX);
//
//	stackDump(L);
//
//	Window **pWindow = reinterpret_cast<Window **>(lua_touserdata(L, 1));
//	(*pWindow)->addMenuItem(new MenuItem(text, x, y, callbackFuncRef));
//
//	lua_pop(L, 3);
//
//	return 0;
//}

//int Window_getMenuItem(lua_State * L)
//{
//	
//	Window **pWindow = reinterpret_cast<Window **>(lua_touserdata(L, 1));
//	
//	int index = luaL_checkinteger(L, 2);
//	
//	MenuItem *menuItem = (*pWindow)->menuItems[index];
//
//	
//
//
//	return 1;
//}

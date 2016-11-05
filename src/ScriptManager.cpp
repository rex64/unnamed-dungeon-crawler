#include "ScriptManager.h"
#include "Game.h"
#include "stage/StageManager.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "stage/Stage.h"

ScriptManager* ScriptManager::manager;

ScriptManager::ScriptManager()
{
}


ScriptManager::~ScriptManager()
{
}

void ScriptManager::init() {

	manager = this;

	//Lua
	m_L = luaL_newstate();
	luaL_openlibs(m_L);

	/*
	lua_register(m_L, "luaTestFunc", luaTestFunc);

	luaL_dostring(m_L, "io.write(\"luaTestFunc\")");
	luaL_dostring(m_L, "luaTestFunc(\"First\", \"Second\", 112233)");

	luaL_dostring(m_L, "io.write(\"ciao\")");
	*/

	/*
	lua_newtable(state);
	lua_setglobal(state, "game");

	lua_getglobal(state, "game");
	lua_pushstring(state, "system");
	lua_newtable(state);
	lua_settable(state, -3);
	lua_pop(state, -1);
	*/

	//data
	lua_newtable(m_L);
	lua_setglobal(m_L, "data");

	//data - reload()
	/*lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "setTile");
	lua_pushcfunction(m_L, l_setTile);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);*/

	//game
	lua_newtable(m_L);
	lua_setglobal(m_L, "game");

	//ui
	lua_newtable(m_L);
	lua_setglobal(m_L, "ui");

	//field
	lua_newtable(m_L);
	lua_setglobal(m_L, "field");

	//field - setTile(id, value)
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "setTile");
	lua_pushcfunction(m_L, l_setTile);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);

	//field - spawnEntity(id, value)
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "spawnEntity");
	lua_pushcfunction(m_L, l_setTile);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);

	//battle
	lua_newtable(m_L);
	lua_setglobal(m_L, "battle");

	//system
	lua_newtable(m_L);
	lua_setglobal(m_L, "system");

	//system.quit
	lua_getglobal(m_L, "system");
	lua_pushstring(m_L, "quit");
	lua_pushcfunction(m_L, luaQuitGame);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);


	luaL_requiref(m_L, "MyLib", luaopen_MyLib, 1);
	stackDump(m_L);
}

bool ScriptManager::onInput(SDL_Event * e)
{
	//printf("ScriptManager - onInput\n");
	return false;
}

void ScriptManager::runMain() {

	stackDump(m_L);
	if (luaL_dofile(m_L, "data/base/scripts/main.lua")) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		lua_pop(m_L, -1);
		stackDump(m_L);
	}
}

void ScriptManager::doString(const char *str)
{
	if (luaL_dostring(m_L, str)) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		lua_pop(m_L, -1);
		stackDump(m_L);
	}
}

void ScriptManager::onQuit() {

	lua_close(m_L);

}

//stolen from https://www.lua.org/pil/24.2.3.html
void stackDump(lua_State *L) {

	printf("LUA STACK DUMP--------\n");

	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

		case LUA_TSTRING:  /* strings */
			printf("`%s'", lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			printf(lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			printf("%g", lua_tonumber(L, i));
			break;

		default:  /* other values */
			printf("%s", lua_typename(L, t));
			break;

		}
		printf("  ");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

//http://www.lua.org/manual/5.3/manual.html#lua_CFunction
int luaTestFunc(lua_State* state)
{
	/* number of arguments */
	int args = lua_gettop(state);

	for (int n = 1; n <= args; ++n) {
		printf("  arg %d: '%s'\n", n, lua_tostring(state, n));
	}

	lua_pushnumber(state, 123);
	return 1; /* number of results */
}

int l_setTile(lua_State* state)
{
	/* number of arguments */
	int args = lua_gettop(state);

	int id = lua_tointeger(state, 1);
	std::string value = lua_tostring(state, 2);
	int tileType = lua_tointeger(state, 3);


	StageManager::manager->currStage->setTile(id, value, (TileType)tileType);
	return 0; /* number of results */
}

int luaQuitGame(lua_State* state) {

	//    printf("luaQuitGame..\n");

	//quit = true;

	Game::game->quit();

	return 0;
}

const static char *Entity_typename = "EntityTypename";

Entity* check_Entity(lua_State *L) {
	return (Entity*) luaL_checkudata(L, 1, Entity_typename);
}

int MyLib_MakeEntity(lua_State *L) {
	
	Entity *e = (Entity*) lua_newuserdata(L, sizeof(Entity));
	luaL_setmetatable(L, Entity_typename);

	e->id = -1;
	e->tileId = -1;
	e->type = Other;
	e->entityResID = std::string("data.base.spritesheets.stairs");

	StageManager::manager->currStage->addEntity(e, 1 + 18);

	printf("Entity Creata");

	return 1;
}
int Entity__gc(lua_State *L) {
	Entity *e = check_Entity(L);
	printf("In Obj__gc\n");
	return 0;
}
int Entity_method(lua_State *L) {
	printf("In Obj_method\n");
	check_Entity(L);
	return 0;
}

int luaopen_MyLib(lua_State *L) {
	static const luaL_Reg Obj_lib[] = {
		{ "method", &Entity_method },
		{ NULL, NULL }
	};

	static const luaL_Reg MyLib_lib[] = {
		{ "MakeObj", &MyLib_MakeEntity },
		{ NULL, NULL }
	};

	stackDump(L);
	luaL_newlib(L, MyLib_lib);
	stackDump(L);

	// Stack: MyLib
	luaL_newmetatable(L, Entity_typename); // Stack: MyLib meta
	stackDump(L);

	luaL_newlib(L, Obj_lib);
	stackDump(L);
	
	lua_setfield(L, -2, "__index"); // Stack: MyLib meta
	stackDump(L);

	lua_pushstring(L, "__gc");
	stackDump(L);

	lua_pushcfunction(L, Entity__gc); // Stack: MyLib meta "__gc" fptr
	stackDump(L);
	
	lua_settable(L, -3); // Stack: MyLib meta
	stackDump(L);

	lua_pop(L, 1); // Stack: MyLib
	stackDump(L);

	return 1;
}

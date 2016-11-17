#include "ScriptManager.h"
#include "Game.h"
#include "stage/StageManager.h"
#include "ui/ui_lua_bindings.h"

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

	//field - addEntity(id, value)
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "addEntity");
	lua_pushcfunction(m_L, l_addEntity);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);

	//field - addEntity(id, value)
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "setEntityTile");
	lua_pushcfunction(m_L, l_setEntityTile);
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

	//data
	lua_newtable(m_L);
	lua_setglobal(m_L, "data");

	//data.entities
	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "entities");
	lua_newtable(m_L);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);

	//data.entities
	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "dungeons");
	lua_newtable(m_L);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);

	/*stackDump(m_L);
	stackDump(m_L);*/

	//TEST
	luaL_requiref(m_L, "MyLib", &luaopen_Windowlib, 1);
}

bool ScriptManager::onInput(SDL_Event * e)
{
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

void ScriptManager::doFile(const char *str){
	if (luaL_dofile(m_L, str)) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		lua_pop(m_L, -1);
		stackDump(m_L);
	}
}

void ScriptManager::onQuit() {

	lua_close(m_L);

}

void ScriptManager::onInteract(std::string s) {

	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "entities");
	lua_gettable(m_L, -2);
	lua_getfield(m_L, -1, s.c_str());
	lua_getfield(m_L, -1, "onInteract");
	
	if (lua_pcall(m_L, 0, 0, 0)) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
	}

	lua_pop(m_L, 3);

}

void ScriptManager::onCreateFloor(std::string s, int floorNo) {

	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "dungeons");
	lua_gettable(m_L, -2);
	lua_getfield(m_L, -1, s.c_str());
	lua_getfield(m_L, -1, "onCreateFloor");

	lua_pushinteger(m_L, floorNo);   /* push 1st argument */

	if (lua_pcall(m_L, 1, 0, 0)) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
	}

	lua_pop(m_L, 3);

}

//stolen from https://www.lua.org/pil/24.2.3.html
void stackDump(lua_State *L) {

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "LUA STACK DUMP--------");

	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

		case LUA_TSTRING:  /* strings */
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "`%s'", lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%g", lua_tonumber(L, i));
			break;

		default:  /* other values */
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, lua_typename(L, t));
			break;

		}
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, " "); /* put a separator */
	}
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "\n"); /* end the listing */

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "--------");
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

int l_addEntity(lua_State* state)
{
	/* number of arguments */
	int args = lua_gettop(state);

	EntityType entityType = (EntityType) lua_tointeger(state, 1);
	std::string entityDataID = lua_tostring(state, 2);

	int newEntityID = StageManager::manager->currStage->addEntity(new Entity{ NULL, NULL, entityType, entityDataID, Up }, -1);

	lua_pushnumber(state, newEntityID);

	return 1; /* number of results */
}

int l_setEntityTile(lua_State* state)
{
	/* number of arguments */
	int args = lua_gettop(state);

	int entityID = lua_tointeger(state, 1);
	int tileID = lua_tointeger(state, 2);

	StageManager::manager->currStage->moveEntity(entityID, tileID);

	return 0; /* number of results */
}

int luaQuitGame(lua_State* state) {

	Game::game->quit();

	return 0;
}

#include "ScriptManager.h"
#include "Game.h"
#include "stage/StageManager.h"
#include "ui/lua_menu.h"
#include "lua_save.h"
#include "lua_data.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "stage/Stage.h"

#include <algorithm>

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
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//game ----------------------------------------------------------
	lua_newtable(m_L);
	lua_setglobal(m_L, "game");
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//ui ----------------------------------------------------------
	lua_newtable(m_L);
	lua_setglobal(m_L, "ui");
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//ui - windows
	lua_getglobal(m_L, "ui");
	lua_pushstring(m_L, "windows");
	lua_newtable(m_L);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//ui - renderWindow
	lua_getglobal(m_L, "ui");
	lua_pushstring(m_L, "renderWindow");
	lua_pushcfunction(m_L, Menu_renderWindow);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//ui - renderMenuItem
	lua_getglobal(m_L, "ui");
	lua_pushstring(m_L, "renderMenuItem");
	lua_pushcfunction(m_L, Menu_renderMenuItem);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//ui - renderSprite
	lua_getglobal(m_L, "ui");
	lua_pushstring(m_L, "renderSprite");
	lua_pushcfunction(m_L, Menu_renderSprite);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//field ----------------------------------------------------------
	lua_newtable(m_L);
	lua_setglobal(m_L, "field");
	checkIfStackIsEmpty(ScriptManager::manager->m_L);


	//field - setTile(id, value)
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "setTile");
	lua_pushcfunction(m_L, l_setTile);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);


	//field - addEntity(id, value)
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "addEntity");
	lua_pushcfunction(m_L, l_addEntity);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);


	//field - setEntityTile
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "setEntityTile");
	lua_pushcfunction(m_L, l_setEntityTile);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//field - onInputUp()
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "onInputUp");
	lua_pushcfunction(m_L, Stage_onInputUp);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//field - onInputRight()
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "onInputRight");
	lua_pushcfunction(m_L, Stage_onInputRight);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//field - onInputDown()
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "onInputDown");
	lua_pushcfunction(m_L, Stage_onInputDown);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//field - onInputLeft()
	lua_getglobal(m_L, "field");
	lua_pushstring(m_L, "onInputLeft");
	lua_pushcfunction(m_L, Stage_onInputLeft);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//battle -------------------------------------------
	lua_newtable(m_L);
	lua_setglobal(m_L, "battle");
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//system -------------------------------------------
	lua_newtable(m_L);
	lua_setglobal(m_L, "system");
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//system.quit
	lua_getglobal(m_L, "system");
	lua_pushstring(m_L, "quit");
	lua_pushcfunction(m_L, luaQuitGame);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//data
	lua_newtable(m_L);
	lua_setglobal(m_L, "data");
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//data.entities
	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "entities");
	lua_newtable(m_L);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//data.dungeons
	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "dungeons");
	lua_newtable(m_L);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//data.skills
	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "skills");
	lua_newtable(m_L);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//data.enemies
	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "enemies");
	lua_newtable(m_L);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//save - getCurrentPartySize
	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "getEnemyData");
	lua_pushcfunction(m_L, Data_getEnemyData);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//save ----------------------------------------------------------
	lua_newtable(m_L);
	lua_setglobal(m_L, "save");
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//save - getCurrentPartySize
	lua_getglobal(m_L, "save");
	lua_pushstring(m_L, "getCurrentPartySize");
	lua_pushcfunction(m_L, Save_getCurrentPartySize);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//save - getPartyMember
	lua_getglobal(m_L, "save");
	lua_pushstring(m_L, "getPartyMemberName");
	lua_pushcfunction(m_L, Save_getPartyMemberName);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//save - getPartyMember
	lua_getglobal(m_L, "save");
	lua_pushstring(m_L, "getHeroSkills");
	lua_pushcfunction(m_L, Save_getHeroSkills);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//save - getSkillName
	lua_getglobal(m_L, "save");
	lua_pushstring(m_L, "getSkillName");
	lua_pushcfunction(m_L, Save_getSkillName);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);


	/*stackDump(m_L);
	stackDump(m_L);*/



	//Load libs
	//luaL_requiref(m_L, "Window", &luaopen_Windowlib, 1);
	//lua_pop(m_L, 1); // requiref leaves the library table on the stack
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

}

void ScriptManager::runMain() {

	stackDump(m_L);

	std::string path = "package.path = package.path .. ';" + std::string(SDL_GetBasePath()) + std::string("data\\base\\scripts\\?.lua'");
	std::replace(path.begin(), path.end(), '\\', '/');

	if (luaL_dostring(m_L, path.c_str())) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		lua_pop(m_L, -1);
		stackDump(m_L);
	}

	if (luaL_dofile(m_L, "data/base/scripts/main.lua")) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		lua_pop(m_L, -1);
		stackDump(m_L);
	}

	if (luaL_dofile(m_L, "data/base/scripts/game.lua")) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		lua_pop(m_L, -1);
		stackDump(m_L);
	}

	if (luaL_dofile(m_L, "data/base/scripts/field.lua")) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		lua_pop(m_L, -1);
		stackDump(m_L);
	}

	if (luaL_dofile(m_L, "data/base/scripts/ui.lua")) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		lua_pop(m_L, -1);
		stackDump(m_L);
	}

	if (luaL_dofile(m_L, "data/base/scripts/battle.lua")) {
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

void ScriptManager::onInputGame(Buttons input) {

	lua_getglobal(m_L, "game");
	lua_pushstring(m_L, "onInput");
	lua_gettable(m_L, 1);

	lua_newtable(m_L);

	//UP	
	lua_pushstring(m_L, "up");
	lua_pushboolean(m_L, input.up);
	lua_settable(m_L, -3);

	//RIGHT
	lua_pushstring(m_L, "right");
	lua_pushboolean(m_L, input.right);
	lua_settable(m_L, -3);

	//DOWN
	lua_pushstring(m_L, "down");
	lua_pushboolean(m_L, input.down);
	lua_settable(m_L, -3);

	//LEFT
	lua_pushstring(m_L, "left");
	lua_pushboolean(m_L, input.left);
	lua_settable(m_L, -3);

	//MENU
	lua_pushstring(m_L, "menu");
	lua_pushboolean(m_L, input.menu);
	lua_settable(m_L, -3);

	if (lua_pcall(m_L, 1, 0, 0) != 0) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
	}

	lua_pop(m_L, 1); //pop game

}

void ScriptManager::updateGame(int dt) {

	lua_getglobal(m_L, "game");
	lua_pushstring(m_L, "update");
	lua_gettable(m_L, 1);

	lua_pushinteger(m_L, dt);

	if (lua_pcall(m_L, 1, 0, 0) != 0) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
	}

	lua_pop(m_L, 1); //pop game

}

bool ScriptManager::weBattle() {

	lua_getglobal(m_L, "battle");
	lua_pushstring(m_L, "weBattle");
	lua_gettable(m_L, 1);

	if (lua_pcall(m_L, 0, 1, 0) != 0) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
	}

	/* retrieve result */
	if (!lua_isboolean(m_L, -1)) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
	}
	bool ret = lua_toboolean(m_L, -1);

	lua_pop(m_L, 1);
	lua_pop(m_L, 1);

	return ret;


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
	printf("-------------\n");  /* end the listing */
}

void checkIfStackIsEmpty(lua_State *L) {

	if (lua_gettop(L)) {
	
		Game::game->showMsgBox("lua stack not empty");
	
	}
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

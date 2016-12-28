#include "ScriptManager.h"
#include "Game.h"
#include "stage/StageManager.h"
#include "ui/lua_menu.h"
#include "lua_save.h"
#include "lua_data.h"
#include "RenderManager.h"
#include "res/ResourceManager.h"
#include "save/SaveManager.h"

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

void ScriptManager::registerGlobalObject(std::string globalObjectName) {

	lua_newtable(m_L);
	lua_setglobal(m_L, globalObjectName.c_str());
	checkIfStackIsEmpty(ScriptManager::manager->m_L);
}

void ScriptManager::registerFunction(std::string globalObjectName, std::string functionName, lua_CFunction function) {

	lua_getglobal(m_L, globalObjectName.c_str());
	lua_pushstring(m_L, functionName.c_str());
	lua_pushcfunction(m_L, function);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);
}

void ScriptManager::registerEmptyObject(std::string globalObjectName, std::string objectName) {
	
	lua_getglobal(m_L, globalObjectName.c_str());
	lua_pushstring(m_L, objectName.c_str());
	lua_newtable(m_L);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);
}

void ScriptManager::init() {

	manager = this;

	//Lua
	m_L = luaL_newstate();
	luaL_openlibs(m_L);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//engine ----------------------------------------------------------
	registerGlobalObject("engine");
	registerFunction("engine", "renderWindow", Menu_renderWindow);
	registerFunction("engine", "renderTextLine", Menu_renderTextLine);
	registerFunction("engine", "renderSprite", Menu_renderSprite);
	registerFunction("engine", "renderSpriteSheet", Render_renderSpriteSheet);

	registerFunction("engine", "setTile", l_setTile);
	registerFunction("engine", "addEntity", l_addEntity);
	registerFunction("engine", "setEntityTile", l_setEntityTile);

	registerFunction("engine", "enableInput", Game_enableInput);
	registerFunction("engine", "disableInput", Game_disableInput);


	/*registerFunction("engine", "onInputUp", Stage_onInputUp);
	registerFunction("engine", "onInputRight", Stage_onInputRight);
	registerFunction("engine", "onInputDown", Stage_onInputDown);
	registerFunction("engine", "onInputLeft", Stage_onInputLeft);*/

	//data ----------------------------------------------------------
	registerGlobalObject("data");
	registerEmptyObject("data", "entities");
	registerEmptyObject("data", "dungeons");
	registerEmptyObject("data", "skills");
	registerEmptyObject("data", "enemies");

	//save - getCurrentPartySize
	lua_getglobal(m_L, "data");
	lua_pushstring(m_L, "getEnemyData");
	lua_pushcfunction(m_L, Data_getEnemyData);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);
	checkIfStackIsEmpty(ScriptManager::manager->m_L);

	//save ----------------------------------------------------------
	registerGlobalObject("save");
	registerFunction("save", "getCurrentPartySize", Save_getCurrentPartySize);
	registerFunction("save", "getPartyMemberId",	Save_getPartyMemberId);
	registerFunction("save", "getPartyMemberName",	Save_getPartyMemberName);
	registerFunction("save", "getPartyMemberStats", Save_getPartyMemberStats);
	registerFunction("save", "getHeroSkills",		Save_getHeroSkills);
	registerFunction("save", "getSkillName",		Save_getSkillName);
	registerFunction("save", "addHero",				Save_addHero);
	registerFunction("save", "heroEquip",			Save_heroEquip);

	registerFunction("engine", "renderTile",		Render_renderTile);
	registerFunction("engine", "renderSprite",		Render_renderSprite);
	registerFunction("engine", "getEntitySpriteId",	Resource_getEntitySpriteId);


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

	//OK
	lua_pushstring(m_L, "ok");
	lua_pushboolean(m_L, input.ok);
	lua_settable(m_L, -3);

	//CANCEL
	lua_pushstring(m_L, "cancel");
	lua_pushboolean(m_L, input.cancel);
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


	//StageManager::manager->currStage->setTile(id, value, (TileType)tileType);
	return 0; /* number of results */
}

int l_addEntity(lua_State* state)
{
	/* number of arguments */
	int args = lua_gettop(state);

	EntityType entityType = (EntityType) lua_tointeger(state, 1);
	std::string entityDataID = lua_tostring(state, 2);

	//int newEntityID = StageManager::manager->currStage->addEntity(new Entity{ NULL, NULL, entityType, entityDataID, Up }, -1);

	//lua_pushnumber(state, newEntityID);

	return 1; /* number of results */
}

int l_setEntityTile(lua_State* state)
{
	/* number of arguments */
	int args = lua_gettop(state);

	int entityID = lua_tointeger(state, 1);
	int tileID = lua_tointeger(state, 2);

	//StageManager::manager->currStage->moveEntity(entityID, tileID);

	return 0; /* number of results */
}

int luaQuitGame(lua_State* state) {

	Game::game->quit();

	return 0;
}

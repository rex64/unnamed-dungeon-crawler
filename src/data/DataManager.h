#pragma once

#ifdef __APPLE__
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#elif _WIN32
#include <lua.hpp>
#endif

#include <unordered_map>
#include <string>
#include <vector>
//#include "IInputReceiver.h"
#include "../res/ResourceManager.h"

class DataManager
{
public:
	DataManager();
	~DataManager();

	static DataManager *manager;
	//std::unordered_map<std::string, Hero*> heroDatas;

	//void addHero(Hero*);

	void init();
	int getCurrentPartySize();
	/*void runMain();
	void doString(const char *str);
	void doFile(const char *str);

	

	bool onInput(SDL_Event* e);
	void onQuit();

	void onInteract(std::string);
	void onCreateFloor(std::string, int);
	bool uiOnInput(int);
	bool weBattle();*/

public:
	//lua_State *m_L;
};

//extern "C" void stackDump(lua_State *L);
//extern "C" void checkIfStackIsEmpty(lua_State *L);
//extern "C" int luaTestFunc(lua_State* state);
//extern "C" int luaQuitGame(lua_State* state);
//extern "C" int l_setTile(lua_State* state);
//extern "C" int l_addEntity(lua_State* state);
//extern "C" int l_setEntityTile(lua_State* state);
//extern "C" int luaopen_MyLib(lua_State *L);

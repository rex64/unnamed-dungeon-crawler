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

class EquipSave {

public:
	std::string id;

	EquipSave(std::string id) { this->id; };
};

class HeroSave {

public:
	
	std::string id;

	EquipSave* weapon;
	EquipSave* head;
	EquipSave* body;
	EquipSave* accessory;

	HeroSave(std::string id) : 
		weapon(nullptr),
		head(nullptr),
		body(nullptr),
		accessory(nullptr)
		{ this->id = id; };

};

class SaveManager
{
public:
	SaveManager();
	~SaveManager();

	static SaveManager *manager;
	//std::unordered_map<std::string, Hero*> heroDatas;
	std::vector<HeroSave*> heroes;

	//void addHero(Hero*);

	void init();
	//int getCurrentPartySize();
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

extern "C" {

	int Save_addHero(lua_State *L);
	int Save_heroEquip(lua_State *L);
	int Save_getPartyMemberId(lua_State *L);
	int Save_getCurrentPartySize(lua_State *L);
	int Save_getPartyMemberName(lua_State *L);
	int Save_getHeroSkills(lua_State *L);
	int Save_getSkillName(lua_State *L);

}

//extern "C" void stackDump(lua_State *L);
//extern "C" void checkIfStackIsEmpty(lua_State *L);
//extern "C" int luaTestFunc(lua_State* state);
//extern "C" int luaQuitGame(lua_State* state);
//extern "C" int l_setTile(lua_State* state);
//extern "C" int l_addEntity(lua_State* state);
//extern "C" int l_setEntityTile(lua_State* state);
//extern "C" int luaopen_MyLib(lua_State *L);

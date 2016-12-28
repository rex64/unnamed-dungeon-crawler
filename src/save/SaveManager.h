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

	EquipSave(std::string id) { this->id = id; };
};

class HeroSave {

public:
	
	std::string id;

	//unsigned int level;
	unsigned int exp;
	EquipSave* weapon;
	EquipSave* head;
	EquipSave* body;
	EquipSave* accessory;

	HeroSave(std::string id) : 
		exp(1),
		weapon(nullptr),
		head(nullptr),
		body(nullptr),
		accessory(nullptr)
		{ this->id = id; };

	static unsigned int getLevel(unsigned int exp) {
		
		if (exp >= 15626) { return 50; };
		if (exp >= 14707) { return 49; };
		if (exp >= 13825) { return 48; };
		if (exp >= 12978) { return 47; };
		if (exp >= 12168) { return 46; };
		if (exp >= 11391) { return 45; };
		if (exp >= 10649) { return 44; };
		if (exp >= 9939) { return 43; };
		if (exp >= 9262) { return 42; };
		if (exp >= 8616) { return 41; };
		if (exp >= 8001) { return 40; };
		if (exp >= 7415) { return 39; };
		if (exp >= 6860) { return 38; };
		if (exp >= 6332) { return 37; };
		if (exp >= 5833) { return 36; };
		if (exp >= 5360) { return 35; };
		if (exp >= 4914) { return 34; };
		if (exp >= 4493) { return 33; };
		if (exp >= 4097) { return 32; };
		if (exp >= 3724) { return 31; };
		if (exp >= 3376) { return 30; };
		if (exp >= 3049) { return 29; };
		if (exp >= 2745) { return 28; };
		if (exp >= 2461) { return 27; };
		if (exp >= 2198) { return 26; };
		if (exp >= 1954) { return 25; };
		if (exp >= 1729) { return 24; };
		if (exp >= 1521) { return 23; };
		if (exp >= 1332) { return 22; };
		if (exp >= 1158) { return 21; };
		if (exp >= 1001) { return 20; };
		if (exp >= 858) { return 19; };
		if (exp >= 730) { return 18; };
		if (exp >= 615) { return 17; };
		if (exp >= 513) { return 16; };
		if (exp >= 422) { return 15; };
		if (exp >= 344) { return 14; };
		if (exp >= 275) { return 13; };
		if (exp >= 217) { return 12; };
		if (exp >= 167) { return 11; };
		if (exp >= 126) { return 10; };
		if (exp >= 92) { return 9; };
		if (exp >= 65) { return 8; };
		if (exp >= 43) { return 7; };
		if (exp >= 28) { return 6; };
		if (exp >= 16) { return 5; };
		if (exp >= 9) { return 4; };
		if (exp >= 4) { return 3; };
		if (exp >= 2) { return 2; };
		if (exp >= 0) { return 1; };


		return -1;
	}

	static unsigned int getTotalExpNeeded(unsigned int level) {

		if (level == 50) { return 15626; };
		if (level == 49) { return 14707; };
		if (level == 48) { return 13825; };
		if (level == 47) { return 12978; };
		if (level == 46) { return 12168; };
		if (level == 45) { return 11391; };
		if (level == 44) { return 10649; };
		if (level == 43) { return 9939; };
		if (level == 42) { return 9262; };
		if (level == 41) { return 8616; };
		if (level == 40) { return 8001; };
		if (level == 39) { return 7415; };
		if (level == 38) { return 6860; };
		if (level == 37) { return 6332; };
		if (level == 36) { return 5833; };
		if (level == 35) { return 5360; };
		if (level == 34) { return 4914; };
		if (level == 33) { return 4493; };
		if (level == 32) { return 4097; };
		if (level == 31) { return 3724; };
		if (level == 30) { return 3376; };
		if (level == 29) { return 3049; };
		if (level == 28) { return 2745; };
		if (level == 27) { return 2461; };
		if (level == 26) { return 2198; };
		if (level == 25) { return 1954; };
		if (level == 24) { return 1729; };
		if (level == 23) { return 1521; };
		if (level == 22) { return 1332; };
		if (level == 21) { return 1158; };
		if (level == 20) { return 1001; };
		if (level == 19) { return 858; };
		if (level == 18) { return 730; };
		if (level == 17) { return 615; };
		if (level == 16) { return 513; };
		if (level == 15) { return 422; };
		if (level == 14) { return 344; };
		if (level == 13) { return 275; };
		if (level == 12) { return 217; };
		if (level == 11) { return 167; };
		if (level == 10) { return 126; };
		if (level == 9) { return 92; };
		if (level == 8) { return 65; };
		if (level == 7) { return 43; };
		if (level == 6) { return 28; };
		if (level == 5) { return 16; };
		if (level == 4) { return 9; };
		if (level == 3) { return 4; };
		if (level == 2) { return 2; };
		if (level == 1) { return 0; };

		return -1;
	}

};

class SaveManager
{
public:
	SaveManager();
	~SaveManager();

	static SaveManager *manager;
	std::unordered_map<std::string, HeroSave*> heroMap;
	std::vector<HeroSave*> heroesVector;

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
	int Save_getPartyMemberStats(lua_State *L);
	int Save_getPartyMemberEquip(lua_State *L);
	int Save_getHeroSkills(lua_State *L);
	int Save_getSkillName(lua_State *L);
	int Save_partyMemberCurrentTotalExp(lua_State *L);
	int Save_getExpToLevel(lua_State *L);

}

//extern "C" void stackDump(lua_State *L);
//extern "C" void checkIfStackIsEmpty(lua_State *L);
//extern "C" int luaTestFunc(lua_State* state);
//extern "C" int luaQuitGame(lua_State* state);
//extern "C" int l_setTile(lua_State* state);
//extern "C" int l_addEntity(lua_State* state);
//extern "C" int l_setEntityTile(lua_State* state);
//extern "C" int luaopen_MyLib(lua_State *L);

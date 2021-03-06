#include "lua_data.h"
#include <stdio.h>
#include "ScriptManager.h"
//#include "SaveManager.h"
#include "res/ResourceManager.h"

int Data_getEnemyData(lua_State *L) {


	std::string enemyId = lua_tostring(L, 1);
	EnemyData *enemyData = ResourceManager::manager->getEnemyData(enemyId);

	lua_newtable(L);

	//name
	lua_pushstring(L, "name");
	lua_pushstring(L, enemyData->name.c_str());
	lua_settable(L, -3);

	//level
	lua_pushstring(L, "level");
	lua_pushinteger(L, enemyData->level);
	lua_settable(L, -3);

	//hp;
	lua_pushstring(L, "hp");
	lua_pushinteger(L, enemyData->hp);
	lua_settable(L, -3);

	//atk;
	lua_pushstring(L, "atk");
	lua_pushinteger(L, enemyData->atk);
	lua_settable(L, -3);

	//def;
	lua_pushstring(L, "def");
	lua_pushinteger(L, enemyData->def);
	lua_settable(L, -3);

	//matk;
	lua_pushstring(L, "matk");
	lua_pushinteger(L, enemyData->matk);
	lua_settable(L, -3);

	//mdef;
	lua_pushstring(L, "mdef");
	lua_pushinteger(L, enemyData->mdef);
	lua_settable(L, -3);

	//mnd;
	lua_pushstring(L, "mnd");
	lua_pushinteger(L, enemyData->mnd);
	lua_settable(L, -3);

	//spd;
	lua_pushstring(L, "spd");
	lua_pushinteger(L, enemyData->spd);
	lua_settable(L, -3);

	//lck;
	lua_pushstring(L, "lck");
	lua_pushinteger(L, enemyData->lck);
	lua_settable(L, -3);

	return 1;
}

//int Save_getCurrentPartySize(lua_State *L) {
//
//	int x = lua_tointeger(L, 1);
//	int y = lua_tointeger(L, 2);
//	int h = lua_tointeger(L, 3);
//	int w = lua_tointeger(L, 4);
//
//	int curPartySize = SaveManager::manager->getCurrentPartySize();
//
//	lua_pushinteger(L, curPartySize);
//
//	return 1;
//}
//
//int Save_getPartyMemberName(lua_State *L) {
//
//	int y = lua_tointeger(L, 1);
//
//	int i = 1;
//
//	for (auto kv : SaveManager::manager->heroDatas)
//	{
//		if (i == y) {
//			Hero *h = kv.second;
//			lua_pushstring(L, h->getHeroName().c_str());
//			break;
//		}
//
//		i++;
//	}
//
//	return 1;
//}
//
//int Save_getHeroSkills(lua_State *L) {
//
//	int y = lua_tointeger(L, 1);
//
//	int i = 1;
//
//	Hero *h = nullptr;
//
//	for (auto kv : SaveManager::manager->heroDatas)
//	{
//		if (i == y) {
//			h = kv.second;
//			break;
//		}
//
//		i++;
//	}
//
//	std::vector<std::string> res;
//
//	for (auto e : h->equips) {
//	
//		for (auto s : e->skillIds) {
//			
//			res.push_back(s);
//		}
//	}
//
//	lua_newtable(L);
//
//	int x = 1;
//	for (auto s : res) {
//		
//		lua_pushstring(L, s.c_str());
//		lua_rawseti(L, -2, x);
//
//		x++;
//	}
//
//	return 1;
//}
//
//int Save_getSkillName(lua_State *L) {
//
//	std::string skillId = lua_tostring(L, 1);
//
//	std::string skillName = ResourceManager::manager->getSkillData(skillId)->name;
//
//	lua_pushstring(L, skillName.c_str());
//
//	return 1;
//}
#include "SaveManager.h"
#include "../Game.h"
#include "../stage/StageManager.h"
#include "../ui/lua_menu.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "../stage/Stage.h"

SaveManager* SaveManager::manager;

SaveManager::SaveManager()
{
}


SaveManager::~SaveManager()
{
}

void SaveManager::init() {

	manager = this;
}

//void SaveManager::addHero(Hero *newHero) {
//
//	heroDatas[newHero->heroDataId] = newHero;
//}

//int SaveManager::getCurrentPartySize() {
//
//	return 4;
//}

int Save_addHero(lua_State *L) {

	std::string heroId = lua_tostring(L, 1);
	int heroPosition = lua_tointeger(L, 2);

	HeroData *heroData = ResourceManager::manager->getHeroData(heroId);

	SaveManager::manager->heroes.push_back(new HeroSave(heroData->id));

	return 0;

}
int Save_heroEquipEquip(lua_State *L) {

	std::string heroId = lua_tostring(L, 1);
	std::string equipId = lua_tostring(L, 2);

	HeroSave *heroSave = nullptr;
	for (auto h : SaveManager::manager->heroes)
	{
		if (h->id == heroId) { heroSave = h; };
	}

	EquipData *equipData = ResourceManager::manager->getEquipData(equipId);

	switch (equipData->type)
	{
	WEAPON:
		heroSave->weapon = new EquipSave(equipData->id);
		break;
	default:
		Game::game->showMsgBox("Save_heroEquipEquip - equipData->type LOL");
		break;
	}

	return 0;
}

int Save_getCurrentPartySize(lua_State *L) {

	int x = lua_tointeger(L, 1);
	int y = lua_tointeger(L, 2);
	int h = lua_tointeger(L, 3);
	int w = lua_tointeger(L, 4);

	int curPartySize = 4;

	lua_pushinteger(L, curPartySize);

	return 1;
}

int Save_getPartyMemberName(lua_State *L) {

	/*int y = lua_tointeger(L, 1);

	int i = 1;

	for (auto kv : DataManager::manager->heroDatas)
	{
	if (i == y) {
	Hero *h = kv.second;
	lua_pushstring(L, h->getHeroName().c_str());
	break;
	}

	i++;
	}*/

	lua_pushstring(L, "noheroname");

	return 1;
}

int Save_getHeroSkills(lua_State *L) {

	/*int y = lua_tointeger(L, 1);

	int i = 1;

	Hero *h = nullptr;

	for (auto kv : DataManager::manager->heroDatas)
	{
	if (i == y) {
	h = kv.second;
	break;
	}

	i++;
	}

	std::vector<std::string> res;

	for (auto e : h->equips) {

	for (auto s : e->skillIds) {

	res.push_back(s);
	}
	}

	lua_newtable(L);

	int x = 1;
	for (auto s : res) {

	lua_pushstring(L, s.c_str());
	lua_rawseti(L, -2, x);

	x++;
	}*/

	lua_newtable(L);

	lua_pushstring(L, "noskillid");
	lua_rawseti(L, -2, 1);

	return 1;
}

int Save_getSkillName(lua_State *L) {

	/*std::string skillId = lua_tostring(L, 1);

	std::string skillName = ResourceManager::manager->getSkillData(skillId)->name;

	lua_pushstring(L, skillName.c_str());*/

	lua_pushstring(L, "noskillname");

	return 1;
}
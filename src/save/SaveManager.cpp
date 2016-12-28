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

	/*unsigned int expToLevel0	= HeroSave::getTotalExpNeeded(1);
	unsigned int expToLevel4 = HeroSave::getTotalExpNeeded(4);
	unsigned int expToLevel5 = HeroSave::getTotalExpNeeded(5);
	unsigned int expToLevel10 = HeroSave::getTotalExpNeeded(10);
	unsigned int expToLevel20 = HeroSave::getTotalExpNeeded(20);
	unsigned int expToLevel25 = HeroSave::getTotalExpNeeded(25);

	unsigned int expToLevel50	= HeroSave::getTotalExpNeeded(50);

	unsigned int expToLeve1 = HeroSave::getLevel(expToLevel0);
	unsigned int expToLeve4 = HeroSave::getLevel(expToLevel4);
	unsigned int expToLeve5 = HeroSave::getLevel(expToLevel5);
	unsigned int expToLeve10 = HeroSave::getLevel(expToLevel10);
	unsigned int expToLeve20 = HeroSave::getLevel(expToLevel20);
	unsigned int expToLeve25 = HeroSave::getLevel(expToLevel25);
	unsigned int expToLeve50 = HeroSave::getLevel(expToLevel50);



	unsigned int expToLevelx0 = HeroSave::getLevel(0);*/


}

int Save_addHero(lua_State *L) {

	std::string heroId = lua_tostring(L, 1);
	int heroPosition = lua_tointeger(L, 2);

	HeroData *heroData = ResourceManager::manager->getHeroData(heroId);

	if (heroData != nullptr) {
		
		HeroSave* newHeroSave = new HeroSave(heroData->id);

		SaveManager::manager->heroMap[heroData->id] = newHeroSave;
		SaveManager::manager->heroesVector.push_back(newHeroSave);

	} else {
	
		Game::game->showMsgBox("Save_addHero - hero: " + heroId + " not found");

	}


	return 0;

}
int Save_heroEquip(lua_State *L) {

	std::string heroId = lua_tostring(L, 1);
	std::string equipId = lua_tostring(L, 2);

	HeroSave *heroSave = nullptr;
	for (auto h : SaveManager::manager->heroesVector)
	{
		if (h->id == heroId) { heroSave = h; };
	}

	EquipData *equipData = ResourceManager::manager->getEquipData(equipId);

	switch (equipData->type)
	{
	case WEAPON:
		heroSave->weapon = new EquipSave(equipData->id);
		break;
	default:
		Game::game->showMsgBox("Save_heroEquipEquip - equipData->type LOL");
		break;
	}

	return 0;
}

int Save_getCurrentPartySize(lua_State *L) {

	int curPartySize = SaveManager::manager->heroesVector.size();

	lua_pushinteger(L, curPartySize);

	return 1;
}

int Save_getPartyMemberId(lua_State *L) {

	int pos = lua_tointeger(L, 1);

	HeroSave *heroSave = nullptr;
	int i = 1;
	for (auto h : SaveManager::manager->heroesVector)
	{
		if (i == pos) {

			HeroData *heroData = ResourceManager::manager->getHeroData(h->id);
			lua_pushstring(L, heroData->id.c_str());
		}

		i++;
	}

	return 1;
}

int Save_getPartyMemberName(lua_State *L) {

	std::string id = lua_tostring(L, 1);
	std::string heroName = ResourceManager::manager->getHeroData(id)->name;
	lua_pushstring(L, heroName.c_str());

	return 1;
}

int Save_getPartyMemberStats(lua_State *L) {

	std::string id = lua_tostring(L, 1);
	HeroData *heroData = ResourceManager::manager->getHeroData(id);
	HeroSave *heroSave = SaveManager::manager->heroMap[id];
	Stats *stat = &heroData->stats[heroSave->getLevel(heroSave->exp) - 1];

	lua_newtable(L);

	//level
	lua_pushstring(L, "level");
	lua_pushinteger(L, stat->levelNo);
	lua_settable(L, -3);

	//int hp;
	lua_pushstring(L, "hp");
	lua_pushinteger(L, stat->hp);
	lua_settable(L, -3);

	//int mp;
	lua_pushstring(L, "mp");
	lua_pushinteger(L, stat->mp);
	lua_settable(L, -3);

	//int atk;
	lua_pushstring(L, "atk");
	lua_pushinteger(L, stat->atk);
	lua_settable(L, -3);

	//int def;
	lua_pushstring(L, "def");
	lua_pushinteger(L, stat->def);
	lua_settable(L, -3);

	//int matk;
	lua_pushstring(L, "matk");
	lua_pushinteger(L, stat->matk);
	lua_settable(L, -3);

	//int mdef;
	lua_pushstring(L, "mdef");
	lua_pushinteger(L, stat->mdef);
	lua_settable(L, -3);

	//int mnd;
	lua_pushstring(L, "mnd");
	lua_pushinteger(L, stat->mnd);
	lua_settable(L, -3);

	//int spd;
	lua_pushstring(L, "spd");
	lua_pushinteger(L, stat->spd);
	lua_settable(L, -3);

	//int lck;
	lua_pushstring(L, "lck");
	lua_pushinteger(L, stat->lck);
	lua_settable(L, -3);

	return 1;
}

int Save_partyMemberCurrentTotalExp(lua_State *L) {

	std::string id = lua_tostring(L, 1);
	HeroSave *heroSave = SaveManager::manager->heroMap[id];
	
	lua_pushinteger(L, heroSave->exp);

	return 1;
}

int Save_getExpToLevel(lua_State *L) {

	int level = lua_tointeger(L, 1);
	int res = HeroSave::getTotalExpNeeded(level);

	lua_pushinteger(L, res);

	return 1;
}

int Save_getPartyMemberEquip(lua_State *L) {

	std::string id = lua_tostring(L, 1);
	//HeroData *heroData = ResourceManager::manager->getHeroData(id);
	HeroSave *heroSave = SaveManager::manager->heroMap[id];

	lua_newtable(L);

	//weapon
	if (heroSave->weapon) {
		EquipData *weaponData = ResourceManager::manager->getEquipData(heroSave->weapon->id);

		lua_pushstring(L, "weapon");
		lua_pushstring(L, weaponData->name.c_str());
		lua_settable(L, -3);

	} else {
	
		lua_pushstring(L, "weapon");
		lua_pushstring(L, "nil");
		lua_settable(L, -3);

	}
	
	//head
	if (heroSave->head) {
		EquipData *headData = ResourceManager::manager->getEquipData(heroSave->head->id);
		lua_pushstring(L, "head");
		lua_pushstring(L, headData->name.c_str());
		lua_settable(L, -3);
	}
	else {
	
		lua_pushstring(L, "head");
		lua_pushstring(L, "nil");
		lua_settable(L, -3);
	}

	//body
	if (heroSave->body) {
		EquipData *bodyData = ResourceManager::manager->getEquipData(heroSave->body->id);
		lua_pushstring(L, "body");
		lua_pushstring(L, bodyData->name.c_str());
		lua_settable(L, -3);
	}
	else {

		lua_pushstring(L, "body");
		lua_pushstring(L, "nil");
		lua_settable(L, -3);
	}

	//accessory
	if (heroSave->accessory) {
		EquipData *accessoryData = ResourceManager::manager->getEquipData(heroSave->accessory->id);
		lua_pushstring(L, "accessory");
		lua_pushstring(L, accessoryData->name.c_str());
		lua_settable(L, -3);
	}
	else {

		lua_pushstring(L, "accessory");
		lua_pushstring(L, "nil");
		lua_settable(L, -3);
	}

	

	return 1;
}

int Save_getHeroSkills(lua_State *L) {

	std::string id = lua_tostring(L, 1);
	HeroData *heroData = ResourceManager::manager->getHeroData(id);

	std::vector<std::string> res;

	HeroSave *heroSave = SaveManager::manager->heroMap[heroData->id];
	
	//weapon
	if (heroSave->weapon) {
		EquipData *weaponData = ResourceManager::manager->getEquipData(heroSave->weapon->id);
		for (std::string skillId : weaponData->skillsIds) {
			res.push_back(skillId);
		}
	}

	//head
	if (heroSave->head) {
		EquipData *headData = ResourceManager::manager->getEquipData(heroSave->head->id);
		for (std::string skillId : headData->skillsIds) {
			res.push_back(skillId);
		}
	}

	//body
	if (heroSave->body) {
		EquipData *bodyData = ResourceManager::manager->getEquipData(heroSave->body->id);
		for (std::string skillId : bodyData->skillsIds) {
			res.push_back(skillId);
		}
	}

	//accessory
	if (heroSave->accessory) {
		EquipData *accessoryData = ResourceManager::manager->getEquipData(heroSave->accessory->id);
		for (std::string skillId : accessoryData->skillsIds) {
			res.push_back(skillId);
		}
	}

	lua_newtable(L);

	int x = 1;
	for (auto s : res) {

		lua_pushstring(L, s.c_str());
		lua_rawseti(L, -2, x);

		x++;
	}

	return 1;
}

int Save_getSkillName(lua_State *L) {

	std::string skillId = lua_tostring(L, 1);

	std::string skillName = ResourceManager::manager->getSkillData(skillId)->name;

	lua_pushstring(L, skillName.c_str());

	return 1;
}

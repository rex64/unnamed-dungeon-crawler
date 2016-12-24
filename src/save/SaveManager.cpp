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

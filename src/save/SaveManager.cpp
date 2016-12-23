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
		
		SaveManager::manager->heroes.push_back(new HeroSave(heroData->id));

	} else {
	
		Game::game->showMsgBox("Save_addHero - hero: " + heroId + " not found");

	}


	return 0;

}
int Save_heroEquip(lua_State *L) {

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

	int curPartySize = SaveManager::manager->heroes.size();

	lua_pushinteger(L, curPartySize);

	return 1;
}

int Save_getPartyMemberId(lua_State *L) {

	int pos = lua_tointeger(L, 1);

	HeroSave *heroSave = nullptr;
	int i = 1;
	for (auto h : SaveManager::manager->heroes)
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
	res.push_back("base.skills.skilltest1");
	res.push_back("base.skills.magic_blast");
	res.push_back("base.skills.sword_attack");

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
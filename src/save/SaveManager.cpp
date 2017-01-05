#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "../stage/Stage.h"
#include "../Game.h"
#include "../stage/StageManager.h"
#include "../ui/lua_menu.h"
#include "../res/ResourceManager.h"

#include "SaveManager.h"

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
	case HEAD:
		heroSave->head = new EquipSave(equipData->id);
		break;
	case BODY:
		heroSave->body = new EquipSave(equipData->id);
		break;
	case ACCESSORY:
		heroSave->accessory = new EquipSave(equipData->id);
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

	//name
	lua_pushstring(L, "name");
	lua_pushstring(L, heroData->name.c_str());
	lua_settable(L, -3);

	//level
	lua_pushstring(L, "level");
	lua_pushinteger(L, stat->levelNo);
	lua_settable(L, -3);

	//hp;
	lua_pushstring(L, "hp");
	lua_pushinteger(L, stat->hp);
	lua_settable(L, -3);

	//mp;
	lua_pushstring(L, "mp");
	lua_pushinteger(L, stat->mp);
	lua_settable(L, -3);

	//atk;
	lua_pushstring(L, "atk");
	lua_pushinteger(L, stat->atk);
	lua_settable(L, -3);

	//def;
	lua_pushstring(L, "def");
	lua_pushinteger(L, stat->def);
	lua_settable(L, -3);

	//matk;
	lua_pushstring(L, "matk");
	lua_pushinteger(L, stat->matk);
	lua_settable(L, -3);

	//mdef;
	lua_pushstring(L, "mdef");
	lua_pushinteger(L, stat->mdef);
	lua_settable(L, -3);

	//mnd;
	lua_pushstring(L, "mnd");
	lua_pushinteger(L, stat->mnd);
	lua_settable(L, -3);

	//spd;
	lua_pushstring(L, "spd");
	lua_pushinteger(L, stat->spd);
	lua_settable(L, -3);

	//lck;
	lua_pushstring(L, "lck");
	lua_pushinteger(L, stat->lck);
	lua_settable(L, -3);

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
	
	//class skills
	for (std::string skillId : heroData->skillsIds) {
		res.push_back(skillId);
	}	

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

int Save_getEquipName(lua_State *L) {

	std::string equipId = lua_tostring(L, 1);

	std::string equipName = ResourceManager::manager->getEquipData(equipId)->name;

	lua_pushstring(L, equipName.c_str());

	return 1;
}

int Save_getSkillName(lua_State *L) {

	std::string skillId = lua_tostring(L, 1);

	std::string skillName = ResourceManager::manager->getSkillData(skillId)->name;

	lua_pushstring(L, skillName.c_str());

	return 1;
}

int Save_addEquipToInventory(lua_State *L) {

	std::string equipId = lua_tostring(L, 1);

	EquipData *equipData = ResourceManager::manager->getEquipData(equipId);

	switch (equipData->type)
	{
	case WEAPON:
		SaveManager::manager->weaponVector.push_back(equipId);
		break;
	case HEAD:
		SaveManager::manager->headVector.push_back(equipId);
		break;
	case BODY:
		SaveManager::manager->bodyVector.push_back(equipId);
		break;
	case ACCESSORY:
		SaveManager::manager->accessoriesVector.push_back(equipId);
		break;
	default:
		Game::game->showMsgBox("Save_addEquipToBag - equipData->type LOL");
		break;
	}

	return 0;
}

int Save_getInventoryWeapons(lua_State *L) {

	lua_newtable(L);

	int x = 1;
	for (auto weaponId : SaveManager::manager->weaponVector) {

		lua_pushstring(L, weaponId.c_str());
		lua_rawseti(L, -2, x);

		x += 1;
	}

	return 1;

}

int Save_getInventoryHeads(lua_State *L) {

	lua_newtable(L);

	int x = 1;
	for (auto headId : SaveManager::manager->headVector) {

		lua_pushstring(L, headId.c_str());
		lua_rawseti(L, -2, x);

		x += 1;
	}

	return 1;

}

int Save_getInventoryBodies(lua_State *L) {

	lua_newtable(L);

	int x = 1;
	for (auto bodyId : SaveManager::manager->bodyVector) {

		lua_pushstring(L, bodyId.c_str());
		lua_rawseti(L, -2, x);

		x += 1;
	}

	return 1;
}

int Save_getInventoryAccessories(lua_State *L) {

	lua_newtable(L);

	int x = 1;
	for (auto accessoryId : SaveManager::manager->accessoriesVector) {

		lua_pushstring(L, accessoryId.c_str());
		lua_rawseti(L, -2, x);

		x += 1;
	}

	return 1;

}

int Save_swapEquip(lua_State *L) {

	std::string heroId  = lua_tostring(L, 1);
	std::string equipId = lua_tostring(L, 2);

	HeroSave *heroSave = SaveManager::manager->heroMap[heroId];
	EquipData *equipData = ResourceManager::manager->getEquipData(equipId);

	switch (equipData->type)
	{
	case WEAPON: 
	{
		//remove weapon-to-equip from inventory
		auto it = std::find(SaveManager::manager->weaponVector.begin(), SaveManager::manager->weaponVector.end(), equipId);
		if (it != SaveManager::manager->weaponVector.end()) SaveManager::manager->weaponVector.erase(it);

		//add old-weapon to inventory
		SaveManager::manager->weaponVector.push_back(heroSave->weapon->id);

		//equip new-weapon
		heroSave->weapon = new EquipSave(equipId);
	}
	break;
	case HEAD:
	{
		auto it = std::find(SaveManager::manager->headVector.begin(), SaveManager::manager->headVector.end(), equipId);
		if (it != SaveManager::manager->headVector.end()) SaveManager::manager->headVector.erase(it);

		SaveManager::manager->headVector.push_back(heroSave->head->id);

		heroSave->head = new EquipSave(equipId);
	}
		break;
	case BODY:
	{
		auto it = std::find(SaveManager::manager->bodyVector.begin(), SaveManager::manager->bodyVector.end(), equipId);
		if (it != SaveManager::manager->bodyVector.end()) SaveManager::manager->bodyVector.erase(it);

		SaveManager::manager->bodyVector.push_back(heroSave->body->id);

		heroSave->body = new EquipSave(equipId);
	}
		break;
	case ACCESSORY:
	{
		auto it = std::find(SaveManager::manager->accessoriesVector.begin(), SaveManager::manager->accessoriesVector.end(), equipId);
		if (it != SaveManager::manager->accessoriesVector.end()) SaveManager::manager->accessoriesVector.erase(it);

		SaveManager::manager->accessoriesVector.push_back(heroSave->accessory->id);

		heroSave->accessory = new EquipSave(equipId);
	}
		break;
	default:
		Game::game->showMsgBox("Save_heroEquipEquip - equipData->type LOL");
		break;
	}

	return 0;



}

int Save_getPartyMemberHp(lua_State *L) {

	std::string id = lua_tostring(L, 1);
	HeroSave *heroSave = SaveManager::manager->heroMap[id];

	lua_pushinteger(L, heroSave->currentHp);

	return 1;
}

int Save_setPartyMemberHp(lua_State *L) {

	std::string id = lua_tostring(L, 1);
	int currentHp = lua_tointeger(L, 2);

	//HeroData *heroData = ResourceManager::manager->getHeroData(id);
	HeroSave *heroSave = SaveManager::manager->heroMap[id];

	heroSave->currentHp = currentHp;

	return 0;
}

int Save_getPartyMemberExp(lua_State *L) {

	std::string id = lua_tostring(L, 1);
	HeroSave *heroSave = SaveManager::manager->heroMap[id];

	lua_pushinteger(L, heroSave->exp);

	return 1;
}

int Save_setPartyMemberExp(lua_State *L) {

	std::string id	= lua_tostring(L, 1);
	int exp	= lua_tointeger(L, 2);

	//HeroData *heroData = ResourceManager::manager->getHeroData(id);
	HeroSave *heroSave = SaveManager::manager->heroMap[id];

	heroSave->exp = exp;

	return 0;
}

int Save_getPartyMemberLevel(lua_State *L) {

	std::string id = lua_tostring(L, 1);
	HeroSave *heroSave = SaveManager::manager->heroMap[id];

	unsigned int level = heroSave->getLevel(heroSave->exp);

	lua_pushinteger(L, level);

	return 1;
}

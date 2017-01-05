#pragma once

#include <unordered_map>
#include <string>

#ifdef __APPLE__
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#elif _WIN32
#include <lua.hpp>
#endif

struct SDL_Surface;

#include "FieldEntityData.h"
#include "EntityData.h"
#include "DungeonData.h"
#include "CharData.h"
#include "FontData.h"
#include "Stats.h"
#include "HeroData.h"
#include "EquipData.h"
#include "SkillData.h"
#include "EnemyData.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void init();

	void loadDataFolder();

	void loadSprite(std::string resId, std::string filePath, bool);

	EntityData* getEntityData(std::string id);
	SDL_Surface* getSprite(std::string id);
	SDL_Surface* getTile(std::string id);
	FontData* getFont(std::string id);
	SDL_Surface* getBorder(std::string id);
	HeroData* getHeroData(std::string id);
	EquipData* getEquipData(std::string id);
	SkillData* getSkillData(std::string id);
	EnemyData* getEnemyData(std::string id);
	
	void loadBorders(std::string basePath);
	void loadDungeons(std::string basePath);
	void loadEntities(std::string basePath);
	void loadFonts(std::string basePath);
	void loadHeroes(std::string basePath);
	void loadEquips(std::string basePath);
	void loadItems(std::string basePath);
	void loadMenu(std::string basePath);
	void loadScripts(std::string basePath);
	void loadSkills(std::string basePath);
	void loadEnemies(std::string basePath);
	void loadSpritesheets(std::string basePath);
	void loadTiles(std::string basePath);
	void loadEncounters(std::string basePath);
	
	static ResourceManager *manager;

private:

	std::unordered_map<std::string, EntityData*> entityDatas;
	std::unordered_map<std::string, DungeonData*> dungeonDatas;
	std::unordered_map<std::string, FontData*> fontDatas;
	std::unordered_map<std::string, HeroData*> heroDatas;
	std::unordered_map<std::string, EquipData*> equipDatas;
	std::unordered_map<std::string, SkillData*> skillDatas;
	std::unordered_map<std::string, EnemyData*> enemyDatas;

	std::unordered_map<std::string, SDL_Surface*> spritesheets;
	std::string resIdFromPath(std::string path);
	std::string removeFilenameFromPath(std::string filename, std::string path);

	SDL_Surface* spriteDefault;
	SDL_Surface* tileDefault;
	SDL_Surface* charDefault;
	SDL_Surface* borderDefault;
	
};

extern "C" {


	int Resource_getEntitySpriteId(lua_State *L);

}

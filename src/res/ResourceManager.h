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

struct FieldEntityData {

	std::string spritesheet;
};

struct EntityData {
	std::string id;
	std::string fileName;
	std::string name;
	FieldEntityData *data;
};

struct DungeonData {
	std::string id;
	std::string fileName;
	std::string name;
};

struct CharData {

	std::string charz;
	std::string fileName;
	int width;
	SDL_Surface *surfNormal;
	SDL_Surface *surfInverted;

};

struct FontData {
	std::string id;
	std::string fileName;
	std::string filePath;
	std::string name;
	
	int height;

	int hSpacing;
	int vSpacing;

	std::unordered_map<std::string, CharData*> chars;
};

struct HeroData {
	std::string id;
	std::string fileName;
	std::string filePath;
	std::string name;
};

enum EquipType{

	WEAPON = 0, 
	HEAD,
	BODY,
	ACCESSORY

};

struct EquipData {

	std::string id;
	std::string fileName;
	std::string filePath;
	std::string name;
	EquipType type;

	std::vector<std::string> skillsIds;
};

struct SkillData {
	std::string id;
	std::string fileName;
	std::string filePath;
	std::string name;
	std::string script;
};

struct EnemyData {
	std::string id;
	std::string fileName;
	std::string filePath;
	std::string name;
	std::string script;
	int hp;
	int strength;
	int speed;
	int vitality;
	int intelligence;
	int mind;
};



class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void init();

	void loadDataFolder();
	//void walk(std::string);

	void loadSprite(std::string resId, std::string filePath, bool);
	/*void loadTile(std::string f);
	void loadFont(std::string f);
	void loadBorder(std::string f);*/

	SDL_Surface* getSprite(std::string id);
	SDL_Surface* getTile(std::string id);
	FontData* getFont(std::string id);
	SDL_Surface* getBorder(std::string id);
	HeroData* getHeroData(std::string id);
	EquipData* getEquipData(std::string id);
	SkillData* getSkillData(std::string id);
	EnemyData* getEnemyData(std::string id);

	std::string resIdFromPath(std::string path);
	std::string removeFilenameFromPath(std::string filename, std::string path);
	
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




	static ResourceManager *manager;	

	std::unordered_map<std::string, EntityData*> entityDatas;
	std::unordered_map<std::string, DungeonData*> dungeonDatas;
	std::unordered_map<std::string, FontData*> fontDatas;
	std::unordered_map<std::string, HeroData*> heroDatas;
	std::unordered_map<std::string, EquipData*> equipDatas;
	std::unordered_map<std::string, SkillData*> skillDatas;
	std::unordered_map<std::string, EnemyData*> enemyDatas;

private:

	std::unordered_map<std::string, SDL_Surface*> spritesheets;
	

	SDL_Surface* spriteDefault;
	SDL_Surface* tileDefault;
	SDL_Surface* charDefault;
	SDL_Surface* borderDefault;
	
};

extern "C" {


	int Resource_getEntitySpriteId(lua_State *L);

}

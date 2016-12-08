#pragma once

#include <unordered_map>
#include <string>

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
	SDL_Surface *surf;

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




class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void init();

	void loadDataFolder();
	//void walk(std::string);

	void loadSprite(std::string resId, std::string filePath);
	/*void loadTile(std::string f);
	void loadFont(std::string f);
	void loadBorder(std::string f);*/

	SDL_Surface* getSprite(std::string id);
	SDL_Surface* getTile(std::string id);
	FontData* getFont(std::string id);
	SDL_Surface* getBorder(std::string id);

	std::string resIdFromPath(std::string path);
	std::string removeFilenameFromPath(std::string filename, std::string path);
	
	void loadBorders(std::string basePath);
	void loadDungeons(std::string basePath);
	void loadEntities(std::string basePath);
	void loadFonts(std::string basePath);
	void loadHeroes(std::string basePath);
	void loadItems(std::string basePath);
	void loadMenu(std::string basePath);
	void loadScripts(std::string basePath);
	void loadSkills(std::string basePath);
	void loadSpritesheets(std::string basePath);
	void loadTiles(std::string basePath);




	static ResourceManager *manager;	

	std::unordered_map<std::string, EntityData*> entityDatas;
	std::unordered_map<std::string, DungeonData*> dungeonDatas;
	std::unordered_map<std::string, FontData*> fontDatas;

private:

	std::unordered_map<std::string, SDL_Surface*> spritesheets;
	

	SDL_Surface* spriteDefault;
	SDL_Surface* tileDefault;
	SDL_Surface* charDefault;
	SDL_Surface* borderDefault;
	
};

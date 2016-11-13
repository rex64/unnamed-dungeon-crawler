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



class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void init();

	void loadDataFolder();
	void walk(std::string);

	void loadSprite(std::string f);
	void loadTile(std::string f);
	void loadFont(std::string f);
	void loadBorder(std::string f);

	SDL_Surface* getSprite(std::string id);
	SDL_Surface* getTile(std::string id);
	SDL_Surface* getFont(std::string id);
	SDL_Surface* getBorder(std::string id);


	static ResourceManager *manager;	

	std::unordered_map<std::string, EntityData*> entityDatas;
	std::unordered_map<std::string, DungeonData*> dungeonDatas;

private:

	std::unordered_map<std::string, SDL_Surface*> spritesheets;
	

	SDL_Surface* spriteDefault;
	SDL_Surface* tileDefault;
	SDL_Surface* charDefault;
	SDL_Surface* borderDefault;
	
};

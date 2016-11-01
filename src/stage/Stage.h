#pragma once
#include <vector>
#include <string> 
#include <unordered_map>

enum TileType {

	Wall = 0,
	Floor = 1

};

struct Tile {

	std::string tileResID;
	TileType tileType;
};

enum EntityType {

	None = 0,
	Player

};

struct Entity {
	int id;
	int tileId;
	EntityType type;
};

class Stage
{
public:
	Stage();
	~Stage();

	void load();
	void setTile(int, std::string, TileType);
	Tile getTile(int tileId);
	Entity getEntity(int entityId);
	Entity getTileEntity(int tileId);	
	//void addEntity(int tileId, EntityType type);

	int arrayWidth;
	int arrayHeight;

private:

	uint32_t nextEntityId;

	std::vector<Tile> tiles;

	std::unordered_map<int, Entity> entities;
	std::unordered_map<int, Entity> tileEntities;
};

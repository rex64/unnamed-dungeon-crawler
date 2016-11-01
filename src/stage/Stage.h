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
	Player,
	Other

};

struct Entity {
	int id;
	int tileId;
	EntityType type;
	std::string entityResID;
};

class Stage
{
public:
	Stage();
	~Stage();

	void load();
	void setTile(int, std::string, TileType);
	Tile getTile(int tileId);
	Entity* getEntity(int entityId);
	Entity* getTileEntity(int tileId);	
	bool addEntity(Entity*, int);
	bool moveEntity(Entity*, int);
	bool removeEntity(Entity*);
	bool checkIfTileIsWalkable(int tileID);

	int arrayWidth;
	int arrayHeight;
	Entity* player;

	std::unordered_map<int, Entity*> entities;

private:

	int nextEntityId;

	std::vector<Tile> tiles;

	
	std::unordered_map<int, Entity*> tileEntities;
};

#pragma once
#include <vector>
#include <string> 
#include <unordered_map>

struct Point {

	int x;
	int y;

};

enum TileType {

	Wall = 0,
	Floor = 1

};

struct Tile {

	std::string tileResID;
	TileType tileType;
};

enum EntityType {

	Player = 0,
	Enemy = 1,
	Other = 2,

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
	int addEntity(Entity*, int);
	bool moveEntity(int entityId, int tileId);
	bool moveEntity(Entity*, int);
	bool removeEntity(Entity*);
	bool checkIfTileIsWalkable(int tileID);

	int arrayWidth;
	int arrayHeight;
	Entity* player;

	int to1D(Point p);
	int to1D(int x, int y);
	Point toXY(int i);
	bool checkBoundaries(int tileId);

	std::unordered_map<int, Entity*> entities;

private:

	int nextEntityId;

	std::vector<Tile> tiles;

	
	std::unordered_map<int, Entity*> tileEntities;
};

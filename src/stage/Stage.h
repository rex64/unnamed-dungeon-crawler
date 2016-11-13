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

enum Facing {

	Up = 0,
	Right,
	Down,
	Left

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
	std::string entityDataID;
	Facing facing;
};

struct AdjEntitiesFindResult {

	Entity *e;
	Entity *upEntity;
	Entity *leftEntity;
	Entity *downEntity;
	Entity *rightEntity;

};

class Stage
{
public:
	Stage();
	~Stage();

	void load(std::string, int);
	void setTile(int, std::string, TileType);
	Tile getTile(int tileId);
	Entity* getEntity(int entityId);
	Entity* getTileEntity(int tileId);
	int addEntity(Entity*, int);
	bool moveEntity(int entityId, int tileId);
	bool moveEntity(Entity*, int);
	void setEntityFacing(Entity*, Facing);
	bool removeEntity(Entity*);
	bool checkIfTileIsWalkable(int tileID);

	AdjEntitiesFindResult Stage::findAdjacentEntities(Entity*);
	//std::vector<const Entity*> Stage::findAdjacentEntities(int tileId) const;

	int arrayWidth;
	int arrayHeight;
	Entity* player;
	AdjEntitiesFindResult adjEntitiesFindRes;

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

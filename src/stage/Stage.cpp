#include "Stage.h"
#include "../ScriptManager.h"

Stage::Stage()
{
	nextEntityId = 1;
}

Stage::~Stage()
{
}

void Stage::load(std::string dungeonDataID, int dungeonFloor) {

	adjEntitiesFindRes = AdjEntitiesFindResult{ nullptr, nullptr, nullptr, nullptr, nullptr };

	player = nullptr;
	arrayWidth = 16;
	arrayHeight = 9;

	for (size_t i = 0; i < arrayWidth * arrayHeight; i++)
	{
		tiles.push_back(Tile{});
	}

	ScriptManager::manager->onCreateFloor(dungeonDataID, dungeonFloor);

}

void Stage::setTile(int id, std::string value, TileType tileType) {

	tiles[id] = Tile{ value, tileType};
}

Tile Stage::getTile(int id) {

	return tiles[id];
}

Entity* Stage::getEntity(int entityId) {

	return entities[entityId];
}

Entity* Stage::getTileEntity(int tileId) {

	if (checkBoundaries(tileId)) {

		return tileEntities[tileId];

	}

	return nullptr;

}

int Stage::addEntity(Entity *newEntity, int tileId)
{
	int entityID = nextEntityId++;

	newEntity->id = entityID;
	entities[entityID] = newEntity;

	newEntity->tileId = tileId;
	tileEntities[tileId] = newEntity;

	//TODO: refactor priority MAX
	if (newEntity->type == Player) {
		this->player = newEntity;
	}

	return entityID;
}

bool Stage::moveEntity(int entityId, int tileId) {

	if (checkBoundaries(tileId)) {
		if (Entity *e = entities[entityId]) {
			moveEntity(e, tileId);
		}
	}

	return false;
}

bool Stage::moveEntity(Entity *entityToMove, int tileId)
{

	if (checkIfTileIsWalkable(tileId)) {

		tileEntities.erase(entityToMove->tileId);

		entityToMove->tileId = tileId;
		tileEntities[tileId] = entityToMove;

		return true;
	}

	return false;
}

bool Stage::removeEntity(Entity *entityToRemove)
{
	return false;
}

void Stage::setEntityFacing(Entity* e, Facing f) {

	e->facing = f;
}

bool Stage::checkIfTileIsWalkable(int tileID)
{
	//TODO: http://stackoverflow.com/questions/17153038/unordered-map-insert-with-void-as-valnue-is-not-working-properly
	if (getTile(tileID).tileType == Floor && tileEntities[tileID] == nullptr) {
		return true;
	}

	return false;
}

int Stage::to1D(Point p) {

	return to1D(p.x, p.y);
}

int Stage::to1D(int x, int y) {

	return x + arrayWidth*y;
}

Point Stage::toXY(int i) {

	int x = i % arrayWidth;
	int y = (i / arrayWidth) % arrayHeight;

	return Point{ x,y };

}

bool Stage::checkBoundaries(int tileId) {

	if (tileId >= 0 || tileId < tiles.size()) {
		return true;
	}

	return false;
}

AdjEntitiesFindResult Stage::findAdjacentEntities(Entity* e) {

	AdjEntitiesFindResult res = AdjEntitiesFindResult{e, nullptr, nullptr, nullptr, nullptr};

	Point p = toXY(e->tileId);
	if (Entity* upEntity = getTileEntity(to1D(p.x, p.y-1))) {
		res.upEntity = upEntity;
	}

	if (Entity* leftEntity = getTileEntity(to1D(p.x-1, p.y))) {
		res.leftEntity = leftEntity;
	}

	if (Entity* downEntity = getTileEntity(to1D(p.x, p.y+1))) {
		res.downEntity = downEntity;
	}

	if (Entity* rightEntity = getTileEntity(to1D(p.x+1, p.y))) {
		res.rightEntity = rightEntity;
	}

	return res;
}

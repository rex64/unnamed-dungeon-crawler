#include "Stage.h"

Stage::Stage()
{
	nextEntityId = 1;
	addEntity(new Entity{ NULL, NULL, Player, "data.base.spritesheets.player" }, 1 + 16);
	addEntity(new Entity{ NULL, NULL, Other, "data.base.spritesheets.stairs" }, 1 + 18);
	addEntity(new Entity{ NULL, NULL, Other, "data.base.spritesheets.enemy" }, 1 + 24);

}

Stage::~Stage()
{
}

void Stage::load() {

	arrayWidth = 16;
	arrayHeight = 9;

	for (size_t i = 0; i < arrayWidth * arrayHeight; i++)
	{
		tiles.push_back(Tile{});
	}
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

	return tileEntities[tileId];
}

bool Stage::addEntity(Entity *newEntity, int tileId)
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

	return true;
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

bool Stage::checkIfTileIsWalkable(int tileID)
{
	//TODO: http://stackoverflow.com/questions/17153038/unordered-map-insert-with-void-as-value-is-not-working-properly
	if (getTile(tileID).tileType == Floor && tileEntities[tileID] == nullptr) {
		return true;
	}

	return false;
}

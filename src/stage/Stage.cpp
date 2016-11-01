#include "Stage.h"

Stage::Stage()
{
	nextEntityId = 1;
	player = Entity{ nextEntityId++, 1, Player, "data.base.spritesheets.player" };

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

Entity Stage::getEntity(int entityId) {

	return entities[entityId];
}

Entity Stage::getTileEntity(int tileId) {

	return tileEntities[tileId];
}

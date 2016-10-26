#include "Stage.h"

Stage::Stage()
{
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

void Stage::setTile(int id, std::string value) {

	tiles[id] = Tile{ value };
}
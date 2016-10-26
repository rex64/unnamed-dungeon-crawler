#pragma once
#include <vector>
#include <string> 

struct Tile {

	std::string tileResID;

};

class Stage
{
public:
	Stage();
	~Stage();

	void load();
	void setTile(int, std::string);

	std::vector<Tile> tiles;
	int arrayWidth;
	int arrayHeight;

private:
	
};

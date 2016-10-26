#pragma once
#include <vector>
 
class Stage
{
public:
	Stage();
	~Stage();

	void load();
	void setTile(int, int);

	std::vector<int> tiles;
	int arrayWidth;
	int arrayHeight;

private:
	
};

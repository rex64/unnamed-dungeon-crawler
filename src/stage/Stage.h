#pragma once
#include <vector>
 
class Stage
{
public:
	Stage();
	~Stage();

	void load();

	std::vector<int> tiles;
	int arrayWidth;
	int arrayHeight;

private:
	
};

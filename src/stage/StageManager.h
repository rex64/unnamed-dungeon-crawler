#pragma once
#include "Stage.h"

class StageManager
{
public:
	StageManager();
	~StageManager();

	void init();
	static StageManager *manager;
	Stage *currStage;

private:
	
};

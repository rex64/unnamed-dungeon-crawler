#pragma once
#include "Stage.h"
#include "../IInputReceiver.h"

class StageManager : public IInputReceiver
{
public:
	StageManager();
	~StageManager();

	void init();
	static StageManager *manager;
	Stage *currStage;

	bool onInput(SDL_Event* e);

private:
	
};

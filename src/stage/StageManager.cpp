#include "StageManager.h"

StageManager* StageManager::manager;

StageManager::StageManager()
{
}


StageManager::~StageManager()
{
}

void StageManager::init() {

	manager = this;
	currStage = new Stage();
	currStage->load();

}
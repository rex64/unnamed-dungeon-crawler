#include "StageManager.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "../ScriptManager.h"

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

bool StageManager::onInput(SDL_Event * e)
{

	//Process player input
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	bool left = state[SDL_SCANCODE_LEFT];
	bool right = state[SDL_SCANCODE_RIGHT];
	bool up = state[SDL_SCANCODE_UP];
	bool down = state[SDL_SCANCODE_DOWN];

	bool spacebar = state[SDL_SCANCODE_SPACE];

	if (left || right || up || down) {

		if (Entity *player = StageManager::manager->currStage->player) {
			Point p = currStage->toXY(player->tileId);

			if (left) p.x -= 1;
			if (right) p.x += 1;
			if (up) p.y -= 1;
			if (down) p.y += 1;

			StageManager::manager->currStage->moveEntity(player, currStage->to1D(p));

			//find adjacent entities
			StageManager::manager->currStage->adjEntitiesFindRes = StageManager::manager->currStage->findAdjacentEntities(player);
			return true;
		}
	}
	else if (spacebar) {
	
		if (StageManager::manager->currStage->adjEntitiesFindRes.e) {

			if (Entity *e = StageManager::manager->currStage->adjEntitiesFindRes.upEntity) {
			
				printf(e->entityDataID.c_str());
				ScriptManager::manager->onInteract(e->entityDataID);
			}

		}

	
		return true;
	}

	
	

	return false;
}

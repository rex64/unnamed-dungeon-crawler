#include "StageManager.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

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
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	bool left = state[SDL_SCANCODE_LEFT];
	bool right = state[SDL_SCANCODE_RIGHT];
	bool up = state[SDL_SCANCODE_UP];
	bool down = state[SDL_SCANCODE_DOWN];

	if ( !(left || right || up || down) ) {
		return false;
	}

	Entity *player = StageManager::manager->currStage->player;
	Point p = currStage->toXY(player->tileId);

	if (left) p.x -= 1;
	if (right) p.x += 1;
	if (up) p.y -= 1;
	if (down) p.y += 1;

	StageManager::manager->currStage->moveEntity(player, currStage->to1D(p));

	printf("StageManager - onInput\n");
	return true;
}

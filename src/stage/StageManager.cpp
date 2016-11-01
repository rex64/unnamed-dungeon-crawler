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

	Entity *player = &(StageManager::manager->currStage->player);

	if (left) {

		int x = player->tileId % StageManager::manager->currStage->arrayWidth;
		int y = (player->tileId / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

		x -= 1;

		player->tileId = x + StageManager::manager->currStage->arrayWidth*y;
	}
	else

		if (state[SDL_SCANCODE_RIGHT]) {

			int x = player->tileId % StageManager::manager->currStage->arrayWidth;
			int y = (player->tileId / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

			x += 1;

			player->tileId = x + StageManager::manager->currStage->arrayWidth*y;
		}
		else

			if (state[SDL_SCANCODE_UP]) {

				int x = player->tileId % StageManager::manager->currStage->arrayWidth;
				int y = (player->tileId / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

				y -= 1;

				player->tileId = x + StageManager::manager->currStage->arrayWidth*y;
			}
			else

				if (state[SDL_SCANCODE_DOWN]) {

					int x = player->tileId % StageManager::manager->currStage->arrayWidth;
					int y = (player->tileId / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

					y += 1;

					player->tileId = x + StageManager::manager->currStage->arrayWidth*y;
				}


	printf("StageManager - onInput\n");
	return true;
}

#include "StageManager.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "../ScriptManager.h"
#include "../ui/MenuManager.h"

StageManager* StageManager::manager;

StageManager::StageManager()
{
}


StageManager::~StageManager()
{
}

void StageManager::init() {

	manager = this;

}

//void StageManager::onInputUp()
//{
//
//	//if (ScriptManager::manager->weBattle()) { //TODO: hack
//
//	//	return true;
//	//}
//
//	//if (e->key.keysym.sym == SDLK_ESCAPE) {
//
//	//	MenuManager::manager->setVisible(true);
//	//	ScriptManager::manager->doString("ui.openMenu()"); //TODO: lol
//
//	//	return true;
//	//}
//
//	////Process player input
//	//const Uint8 *state = SDL_GetKeyboardState(NULL);
//
//	bool left = false;
//	bool right = false;
//	bool up = true;
//	bool down = false;
//
//	bool spacebar = false;
//
//	if (left || right || up || down) {
//
//		if (Entity *player = StageManager::manager->currStage->player) {
//			Point p = currStage->toXY(player->tileId);
//
//			Facing newFacing = Up;
//
//			if (left) { p.x -= 1; newFacing = Left; }
//			else if (right) { p.x += 1; newFacing = Right; }
//			else if (up) { p.y -= 1; newFacing = Up; }
//			else if (down) { p.y += 1; newFacing = Down; }
//
//			StageManager::manager->currStage->moveEntity(player, currStage->to1D(p));
//
//			//change player entity facing
//			StageManager::manager->currStage->setEntityFacing(player, newFacing);
//
//			//find adjacent entities
//			StageManager::manager->currStage->adjEntitiesFindRes = StageManager::manager->currStage->findAdjacentEntities(player);
//			
//		}
//	}
//	else if (spacebar) {
//	
//		if (StageManager::manager->currStage->adjEntitiesFindRes.e) {
//
//			//UP
//			if (StageManager::manager->currStage->player->facing == Up) {
//
//				if (Entity *e = StageManager::manager->currStage->adjEntitiesFindRes.upEntity) {
//
//					SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, e->entityDataID.c_str());
//					ScriptManager::manager->onInteract(e->entityDataID);
//				}
//			}
//
//			//LEFT
//			if (StageManager::manager->currStage->player->facing == Left) {
//
//				if (Entity *e = StageManager::manager->currStage->adjEntitiesFindRes.leftEntity) {
//
//					SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, e->entityDataID.c_str());
//					ScriptManager::manager->onInteract(e->entityDataID);
//				}
//			}
//
//			//DOWN
//			if (StageManager::manager->currStage->player->facing == Down) {
//
//				if (Entity *e = StageManager::manager->currStage->adjEntitiesFindRes.downEntity) {
//
//					SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, e->entityDataID.c_str());
//					ScriptManager::manager->onInteract(e->entityDataID);
//				}
//			}
//
//			//RIGHT
//			if (StageManager::manager->currStage->player->facing == Right) {
//
//				if (Entity *e = StageManager::manager->currStage->adjEntitiesFindRes.rightEntity) {
//
//					SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, e->entityDataID.c_str());
//					ScriptManager::manager->onInteract(e->entityDataID);
//				}
//			}
//
//		}
//	}
//}

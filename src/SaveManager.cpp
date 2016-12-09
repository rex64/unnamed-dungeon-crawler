#include "SaveManager.h"
#include "Game.h"
#include "stage/StageManager.h"
#include "ui/lua_menu.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "stage/Stage.h"

SaveManager* SaveManager::manager;

SaveManager::SaveManager()
{
}


SaveManager::~SaveManager()
{
}

void SaveManager::init() {

	manager = this;
}

void SaveManager::addHero(Hero *newHero) {

	heroDatas[newHero->heroDataId] = newHero;
}
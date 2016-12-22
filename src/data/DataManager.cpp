#include "DataManager.h"
#include "../Game.h"
#include "../stage/StageManager.h"
#include "../ui/lua_menu.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include "../stage/Stage.h"

DataManager* DataManager::manager;

DataManager::DataManager()
{
}


DataManager::~DataManager()
{
}

void DataManager::init() {

	manager = this;
}

void DataManager::addHero(Hero *newHero) {

	heroDatas[newHero->heroDataId] = newHero;
}

int DataManager::getCurrentPartySize() {

	return heroDatas.size();
}
#include "MenuManager.h"
#include "IInputReceiver.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <iostream>

MenuManager* MenuManager::manager;

MenuManager::MenuManager()
{
}


MenuManager::~MenuManager()
{
}

void MenuManager::init() {

	manager = this;
	b_isVisible = false;

}

bool MenuManager::onInput(SDL_Event * e) {

	if (isVisible()) {
	
		if (e->key.keysym.sym == SDLK_ESCAPE) {

			MenuManager::manager->setVisible(false);

			
		}

		return true;
	}

	return false;
}

void MenuManager::setVisible(bool b) {

	b_isVisible = b;
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MenuManager visibility %s", isVisible() ? "true" : "false");

}

bool MenuManager::isVisible() {

	return b_isVisible;

}

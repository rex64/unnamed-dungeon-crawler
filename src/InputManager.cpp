#include "InputManager.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

InputManager* InputManager::manager;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::init() {

	manager = this;

}

void InputManager::onInput(SDL_Event* e) {

}
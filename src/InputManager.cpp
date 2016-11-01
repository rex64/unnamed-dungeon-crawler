#include "InputManager.h"
#include "IInputReceiver.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <iostream>



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

	printf("--Input Manager - onInput\n");
	for (IInputReceiver* i : inputStack) {
		if (i->onInput(e)) {
			break;
		}
	}

}

void InputManager::registerInput(IInputReceiver *receiver)
{
	inputStack.push_back(receiver);
}

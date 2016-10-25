#pragma once
#include <stack>

class IInputReceiver;
union SDL_Event;

class InputManager
{
public:
	InputManager();
	~InputManager();

	void init();
	void onInput(SDL_Event* e);
	

	static InputManager* manager;
	std::stack<IInputReceiver*> inputStack;
};

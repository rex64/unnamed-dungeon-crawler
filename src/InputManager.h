#pragma once
#include <vector>

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
	std::vector<IInputReceiver*> inputStack;
	void registerInput(IInputReceiver*);
};

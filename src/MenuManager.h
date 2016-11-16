#pragma once
#include <vector>
#include "IInputReceiver.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

class Window {

public:
	//int id;

	SDL_Rect rect;

	Window();
	void draw(SDL_Surface *s);

};

class MenuManager : public IInputReceiver
{
public:
	MenuManager();
	~MenuManager();

	void init();
	bool onInput(SDL_Event* e);
	

	static MenuManager* manager;

	void setVisible(bool);
	bool isVisible();

	void addSelectWindow();

	std::vector<Window*> windows;

private:
	bool b_isVisible;
};

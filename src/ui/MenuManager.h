#pragma once
#include <vector>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

//class MenuItem {
//
//public:
//	int x;
//	int y;
//	std::string text;
//	int callbackRef;
//	MenuItem(std::string s, int x, int y, int callbackRef = -1);
//};
//
//class Window {
//
//public:
//	//int id;
//
//	SDL_Rect rect;
//	SDL_Point margins;
//	//std::vector<MenuItem*> menuItems;
//
//	Window(int x, int y);
//	//void addMenuItem(MenuItem*);
//	void draw(SDL_Surface *s);
//
//};

class MenuManager
{
public:
	MenuManager();
	~MenuManager();

	void init();
	bool onInput(SDL_Event* e);
	

	static MenuManager* manager;

	void setVisible(bool);
	bool isVisible();

	//void addSelectWindow();

	//std::vector<Window*> windows;

private:
	bool b_isVisible;
};

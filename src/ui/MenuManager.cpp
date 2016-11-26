#include "MenuManager.h"
#include "../ui/MenuManager.h"
#include "../res/ResourceManager.h"
#include "../RenderManager.h"

#include <iostream>

Window::Window(int x, int y) {

	rect.x = x;
	rect.y = y;
	rect.w = 8;
	rect.h = 8;

	margins.x = 16;
	margins.y = 8;
}

//void Window::addMenuItem(MenuItem *m) {
//
//	menuItems.push_back(m);
//	
//}

void Window::draw(SDL_Surface *s) {

	SDL_Surface *bmp = ResourceManager::manager->getSprite("data.base.menu.menu-window-border");

	SDL_Rect srcRect = SDL_Rect{ 0 , 0, 8, 8 };

	for (int y = 0; y < rect.h + 1; y++) {
	
		if (y == 0) srcRect.y = 0;
		else if (y == rect.h) srcRect.y = 16;
		else srcRect.y = 8;

		for (int x = 0; x < rect.w + 1; x++) {

			if (x == 0 ) srcRect.x = 0;
			else if (x == rect.w) srcRect.x = 16;
			else srcRect.x = 8;
			
			SDL_Rect dstRect = SDL_Rect{ rect.x + (8 * x), rect.y + (8 * y), 8 , 8  };

			SDL_BlitSurface(bmp, &srcRect, s, &dstRect);

		}
	
	}

	//for(int i = 0; i < menuItems.size(); i++){

	//	MenuItem *m = menuItems[i];
	//	
	//	renderTextLine(m->text, m->x, m->y, ResourceManager::manager->getFont("data.base.fonts.standard_font"), s);
	//}

	


}

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

//void MenuManager::addSelectWindow() {
//
//	Window *newW = new Window();
//	windows.push_back(newW);
//
//	newW->addMenuItem(new MenuItem("Item1"));
//	newW->addMenuItem(new MenuItem("Item2"));
//	newW->addMenuItem(new MenuItem("Item3"));
//}

MenuItem::MenuItem(std::string s, int x, int y, int callbackRef) {
	this->text = s;
	this->x = x;
	this->y = y;
	this->callbackRef = callbackRef;
}

#include "MenuManager.h"
#include "../ui/MenuManager.h"
#include "../res/ResourceManager.h"
#include "../RenderManager.h"
#include "../ScriptManager.h"
#include "../Game.h"

#include <iostream>
#include <sstream>
//
//Window::Window(int x, int y) {
//
//	rect.x = x;
//	rect.y = y;
//	rect.w = 8;
//	rect.h = 8;
//
//	margins.x = 16;
//	margins.y = 8;
//}
//
////void Window::addMenuItem(MenuItem *m) {
////
////	menuItems.push_back(m);
////	
////}
//
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

	//auto button = -1;
	return true;
}

void MenuManager::setVisible(bool b) {

	b_isVisible = b;
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MenuManager visibility %s", isVisible() ? "true" : "false");

}

bool MenuManager::isVisible() {

	return b_isVisible;

}

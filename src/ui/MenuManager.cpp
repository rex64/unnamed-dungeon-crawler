#include "MenuManager.h"
#include "../ui/MenuManager.h"
#include "../res/ResourceManager.h"
#include "../RenderManager.h"
#include "../ScriptManager.h"

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

	//if (isVisible()) {
	
		/*if (e->key.keysym.sym == SDLK_ESCAPE) {

			MenuManager::manager->setVisible(false);

			
		}*/

		auto button = -1;
		const Uint8 *state = SDL_GetKeyboardState(NULL);

			
		if (state[SDL_SCANCODE_UP]) button = 0;
		else if (state[SDL_SCANCODE_RIGHT]) button = 1;
		else if (state[SDL_SCANCODE_DOWN]) button = 2;
		else if (state[SDL_SCANCODE_LEFT]) button = 3;
		else if (state[SDL_SCANCODE_RETURN]) button = 4;
		else if (state[SDL_SCANCODE_BACKSPACE]) button = 5;
		else if (state[SDL_SCANCODE_ESCAPE]) button = 6;

		if (button != -1) {

			//std::ostringstream stringStream;
			//stringStream << "ui.update(" << button << ")"; //TODO: lol
			//std::string copyOfStr = stringStream.str();

			//ScriptManager::manager->doString(copyOfStr.c_str()); //TODO: lol

			return ScriptManager::manager->uiUpdate(button);
		}

		
	//}

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

//MenuItem::MenuItem(std::string s, int x, int y, int callbackRef) {
//	this->text = s;
//	this->x = x;
//	this->y = y;
//	this->callbackRef = callbackRef;
//}

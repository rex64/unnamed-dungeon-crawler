#pragma once
#include <vector>
#include "IInputReceiver.h"

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

private:
	bool b_isVisible;
};

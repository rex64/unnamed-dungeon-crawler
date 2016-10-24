#pragma once
#include "ScriptManager.h"
class Game
{
public:
	Game();
	~Game();

	void init();
	void run();

	void showMsgBox(const char *msg);
	void quit();


	static Game *game;
private:
	bool m_bQuit;
};


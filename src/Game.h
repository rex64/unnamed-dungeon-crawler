#pragma once

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 225

#define GAME_WIDTH 256
#define GAME_HEIGHT 144

struct SDL_Window;

struct Buttons {

	bool up;
	bool right;
	bool down;
	bool left;

	bool ok;
	bool cancel;

	bool menu;
};

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
	SDL_Window *window;
private:
	bool m_bQuit;
};


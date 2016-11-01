#pragma once

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 225

#define GAME_WIDTH 256
#define GAME_HEIGHT 144

struct SDL_Window;

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


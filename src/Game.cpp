#include "Game.h"

#ifdef __APPLE__

#include <SDL2/SDL.h>

#elif _WIN32

#include <SDL.h>
#include <stdio.h>

#endif

#include <string>
#include <unordered_map>
#include <iostream>

#include "res/ResourceManager.h"
#include "stage/StageManager.h"
#include "ScriptManager.h"
#include "Console.h"
#include "InputManager.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 225

#define GAME_WIDTH 256
#define GAME_HEIGHT 144

SDL_Window *window;

Game* Game::game;

struct Entity {
	int pos;
	std::string surfaceStr;
};

void renderTextLine(std::string str, int x, int y, SDL_Surface* charSet, SDL_Surface* surf) {

	if (Console::console->showCursor) {
		str = str + '_';
	}

	int i = 0;
	for (char& c : str) {

		int charIndex = c - 32;
		SDL_Rect src = { 8 * charIndex, 0, 8, 8 };
		SDL_Rect dst = { (8 + x) * i, y * 8 , 8, 8 };

		SDL_BlitSurface(charSet, &src, surf, &dst);
		++i;
	}
}

void renderText(std::string str, SDL_Surface* charSet, SDL_Surface* surf) {

	int i = 0;
	int j = 0;
	for (char& c : str) {
		//printf("%c", c);
		if (((int)c) == 10) {
			++j;
			i = 0;
			continue;
		};
		int charIndex = c - 32;
		SDL_Rect src = { 8 * charIndex, 0, 8, 8 };
		SDL_Rect dst = { 8 * i, (14 + j) * 8 , 8, 8 };

		SDL_BlitSurface(charSet, &src, surf, &dst);
		++i;
	}
}


Game::Game()
{
}


Game::~Game()
{
}

void Game::init() {

	game = this;

	ResourceManager *resManager = new ResourceManager();
	resManager->init();

	Console *console = new Console();
	console->init();

	ScriptManager *scriptManager = new ScriptManager();
	scriptManager->init();

	StageManager *stageManager = new StageManager();
	stageManager->init();

	InputManager *inputManger = new InputManager();
	inputManger->init();

}

extern "C" Uint32 my_callbackfunc(Uint32 interval, void *param)
{
	SDL_Event event;
	SDL_UserEvent userevent;

	/* In this example, our callback pushes a function
	into the queue, and causes our callback to be called again at the
	same interval: */

	/*userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = &my_function;
	userevent.data2 = param;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);*/
	Console::console->showCursor = !Console::console->showCursor;
	return(interval);
}

void Game::run() {

	Entity player = { 0 };
	player.surfaceStr = "data.base.spritesheets.player";

	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"unamed-dungeon-crawler",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH * 2,
		SCREEN_HEIGHT * 2,
		SDL_WINDOW_RESIZABLE
	);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);


	SDL_Texture *texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	//    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	//    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH*4, SCREEN_HEIGHT*4);

	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", SDL_GetError(), window);

	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
	SDL_Surface *game = SDL_CreateRGBSurface(0, GAME_WIDTH, GAME_HEIGHT, 32, 0, 0, 0, 0);

	SDL_Event e;
	
	SDL_StartTextInput();

	m_bQuit = false;

	ScriptManager::manager->runMain();

	SDL_AddTimer(260, my_callbackfunc, 0);

	while (!m_bQuit)
	{

		while (SDL_PollEvent(&e) != 0)
		{

			InputManager::manager->onInput(&e);

			if (e.type == SDL_QUIT)
			{
				m_bQuit = true;
			}

			if (Console::console->visible == true) {

				if (e.key.keysym.sym == SDLK_BACKSPACE) {
					Console::console->cmd = Console::console->cmd.substr(0, Console::console->cmd.length() - 1);
				}
				else if (e.type == SDL_TEXTINPUT) {
					Console::console->cmd = Console::console->cmd + e.text.text;
				}
				else if (e.key.keysym.sym == SDLK_RETURN) {
					ScriptManager::manager->doString(Console::console->cmd.c_str());
					Console::console->cmd = "";

				}
			}

			if (e.type == SDL_TEXTINPUT) {

				if (strcmp(e.text.text, "~") == 0) {
					Console::Console::console->visible = !Console::console->visible;
				}

			}

			//Console
			if (Console::console->visible == true) {
				

			}
			else {

				const Uint8 *state = SDL_GetKeyboardState(NULL);

				/*if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.sym == SDLK_BACKQUOTE) {
						Console::console->visible = !Console::console->visible;
					}
				}*/

				if (state[SDL_SCANCODE_LEFT]) {

					//int oldPos = playerPos;

					int x = player.pos % StageManager::manager->currStage->arrayWidth;
					int y = (player.pos / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

					x -= 1;

					player.pos = x + StageManager::manager->currStage->arrayWidth*y;
				}
				else

					if (state[SDL_SCANCODE_RIGHT]) {

						int x = player.pos % StageManager::manager->currStage->arrayWidth;
						int y = (player.pos / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

						x += 1;

						player.pos = x + StageManager::manager->currStage->arrayWidth*y;
					}
					else

						if (state[SDL_SCANCODE_UP]) {

							int x = player.pos % StageManager::manager->currStage->arrayWidth;
							int y = (player.pos / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

							y -= 1;

							player.pos = x + StageManager::manager->currStage->arrayWidth*y;
						}
						else

							if (state[SDL_SCANCODE_DOWN]) {

								int x = player.pos % StageManager::manager->currStage->arrayWidth;
								int y = (player.pos / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

								y += 1;

								player.pos = x + StageManager::manager->currStage->arrayWidth*y;
							}
			}

		}

		//clear screen surface
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 0));
		SDL_FillRect(game, NULL, SDL_MapRGB(screen->format, 0, 255, 0));

		//render tiles
		for (size_t i = 0; i < StageManager::manager->currStage->arrayWidth * StageManager::manager->currStage->arrayHeight; i++)
		{
			int x = i % StageManager::manager->currStage->arrayWidth;
			int y = (i / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

			SDL_Rect pos = { x * 16, y * 16, 16, 16 };

			SDL_BlitSurface(
				ResourceManager::manager->getTile(StageManager::manager->currStage->tiles[i].tileResID),
				NULL, 
				game, 
				&pos
			);
		}

		//render player
		{

			int x = player.pos % StageManager::manager->currStage->arrayWidth;
			int y = (player.pos / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

			//Player-->Game
			SDL_Rect pos = { x * 16, y * 16, 16, 16 };
			SDL_BlitSurface(ResourceManager::manager->getSprite(player.surfaceStr), NULL, game, &pos);
		}


		//SDL_BlitSurface(testSurface, 0, game, NULL);

		//Border-->Screen
		SDL_BlitSurface(ResourceManager::manager->borders["data.base.borders.border"], 0, screen, 0);

		//TextBox-->Game
		SDL_BlitSurface(ResourceManager::manager->fonts["data.base.fonts.standard_font"], 0, screen, 0);
		renderText("TEXT MESSAGE BOX\nHello World!", ResourceManager::manager->fonts["data.base.fonts.standard_font"], game);

		//Game-->Screen
		SDL_Rect location = { 72,40,100,100 };
		SDL_BlitSurface(game, 0, screen, &location);

		//Console-->Screen
		{
			if (Console::console->visible) {
				SDL_Surface *consoleSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT - 16, 32, 0, 0, 0, 0);
				SDL_FillRect(consoleSurface, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

				renderTextLine(">" + Console::console->cmd, 0, 24, ResourceManager::manager->fonts["data.base.fonts.standard_font"], consoleSurface);

				SDL_BlitSurface(consoleSurface, 0, screen, 0);
				SDL_FreeSurface(consoleSurface);
			}
		}

		SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, 0, 0);
		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}

	printf("Quitting..\n");

	//lua_close(m_L);

	//SDL_FreeSurface(testSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

void Game::showMsgBox(const char *msg)
{
	SDL_ShowSimpleMessageBox(0, "READ CAREFULLY", msg, window);
}

void Game::quit() {

	m_bQuit = true;
}

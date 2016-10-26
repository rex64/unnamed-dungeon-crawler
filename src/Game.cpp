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

	SDL_Init(SDL_INIT_VIDEO);
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

	while (!m_bQuit)
	{

		while (SDL_PollEvent(&e) != 0)
		{

			InputManager::manager->onInput(&e);

			if (e.type == SDL_QUIT)
			{
				m_bQuit = true;
			}

			if (e.type == SDL_TEXTINPUT) {

				if (strcmp(e.text.text, "~") == 0) {
					Console::Console::console->visible = !Console::console->visible;
				}

			}

			//Console
			if (Console::console->visible == true) {

				if (e.type == SDL_KEYDOWN) {

					SDL_Keymod omar = SDL_GetModState();

					if (e.key.keysym.sym == SDLK_q) Console::console->cmd = Console::console->cmd + "q";
					if (e.key.keysym.sym == SDLK_w) Console::console->cmd = Console::console->cmd + "w";
					if (e.key.keysym.sym == SDLK_e) Console::console->cmd = Console::console->cmd + "e";
					if (e.key.keysym.sym == SDLK_r) Console::console->cmd = Console::console->cmd + "r";
					if (e.key.keysym.sym == SDLK_t) Console::console->cmd = Console::console->cmd + "t";
					if (e.key.keysym.sym == SDLK_y) Console::console->cmd = Console::console->cmd + "y";
					if (e.key.keysym.sym == SDLK_u) Console::console->cmd = Console::console->cmd + "u";
					if (e.key.keysym.sym == SDLK_i) Console::console->cmd = Console::console->cmd + "i";
					if (e.key.keysym.sym == SDLK_o) Console::console->cmd = Console::console->cmd + "o";
					if (e.key.keysym.sym == SDLK_p) Console::console->cmd = Console::console->cmd + "p";
					if (e.key.keysym.sym == SDLK_a) Console::console->cmd = Console::console->cmd + "a";
					if (e.key.keysym.sym == SDLK_s) Console::console->cmd = Console::console->cmd + "s";
					if (e.key.keysym.sym == SDLK_d) Console::console->cmd = Console::console->cmd + "d";
					if (e.key.keysym.sym == SDLK_f) Console::console->cmd = Console::console->cmd + "f";
					if (e.key.keysym.sym == SDLK_h) Console::console->cmd = Console::console->cmd + "h";
					if (e.key.keysym.sym == SDLK_j) Console::console->cmd = Console::console->cmd + "j";
					if (e.key.keysym.sym == SDLK_k) Console::console->cmd = Console::console->cmd + "k";
					if (e.key.keysym.sym == SDLK_l) Console::console->cmd = Console::console->cmd + "l";
					if (e.key.keysym.sym == SDLK_z) Console::console->cmd = Console::console->cmd + "z";
					if (e.key.keysym.sym == SDLK_x) Console::console->cmd = Console::console->cmd + "x";
					if (e.key.keysym.sym == SDLK_c) Console::console->cmd = Console::console->cmd + "c";
					if (e.key.keysym.sym == SDLK_v) Console::console->cmd = Console::console->cmd + "v";
					if (e.key.keysym.sym == SDLK_b) Console::console->cmd = Console::console->cmd + "b";
					if (e.key.keysym.sym == SDLK_n) Console::console->cmd = Console::console->cmd + "n";
					if (e.key.keysym.sym == SDLK_m) Console::console->cmd = Console::console->cmd + "m";

					if (e.key.keysym.sym == SDLK_PERIOD) Console::console->cmd = Console::console->cmd + ".";
					if (e.key.keysym.sym == SDLK_SEMICOLON) Console::console->cmd = Console::console->cmd + ";";

					if (e.key.keysym.sym == SDLK_QUOTE) {
						if (e.key.keysym.sym == SDLK_QUOTE && omar & KMOD_SHIFT) {
							Console::console->cmd = Console::console->cmd + "\"";
						}
						else {
							Console::console->cmd = Console::console->cmd + "'";

						}
					}

					if (e.key.keysym.sym == SDLK_9) {
						if (e.key.keysym.sym == SDLK_9 && omar & KMOD_SHIFT) {
							Console::console->cmd = Console::console->cmd + "(";
						}
						else {
							Console::console->cmd = Console::console->cmd + "9";

						}
					}

					if (e.key.keysym.sym == SDLK_0) {
						if (e.key.keysym.sym == SDLK_0 && omar & KMOD_SHIFT) {
							Console::console->cmd = Console::console->cmd + ")";
						}
						else {
							Console::console->cmd = Console::console->cmd + "0";
						}
					}
					if (e.key.keysym.sym == SDLK_SPACE) Console::console->cmd = Console::console->cmd + " ";
					if (e.key.keysym.sym == SDLK_BACKSPACE) Console::console->cmd = Console::console->cmd.substr(0, Console::console->cmd.length() - 1);

				}

				//printf("Console::console: %s\n", Console::console->cmd.c_str());

				if (e.type == SDL_KEYDOWN) {

					//					if (e.key.keysym.sym == SDLK_BACKQUOTE) {
					//						Console::console->visible = !Console::console->visible;
					//					}

					if (e.key.keysym.sym == SDLK_RETURN) {
						ScriptManager::manager->doString(Console::console->cmd.c_str());
						Console::console->cmd = "";

					}
				}

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

			//printf("x: %i , y: %i\n", x, y);

			if (StageManager::manager->currStage->tiles[i] == 0) {

				SDL_BlitSurface(ResourceManager::manager->tiles["data.base.tiles.tile00"], NULL, game, &pos);
			}
			else

				if (StageManager::manager->currStage->tiles[i] == 1) {

					SDL_BlitSurface(ResourceManager::manager->tiles["data.base.tiles.tile01"], NULL, game, &pos);
				}
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

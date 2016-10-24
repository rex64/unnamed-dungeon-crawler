#include "Game.h"

#ifdef __APPLE__

#include <SDL2/SDL.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#elif _WIN32

#include <SDL.h>
#include <stdio.h>
#include <lua.hpp>

#endif

#include <string>
#include <unordered_map>
#include <iostream>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 225

#define GAME_WIDTH 256
#define GAME_HEIGHT 144

bool quit = false;

struct Entity {
	int pos;
	std::string surfaceStr;
};

struct Console {
	bool visible;
	std::string cmd;
	std::string buff;
};

static void stackDump(lua_State *L) {

	printf("LUA STACK DUMP--------\n");

	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

		case LUA_TSTRING:  /* strings */
			printf("`%s'", lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			printf(lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			printf("%g", lua_tonumber(L, i));
			break;

		default:  /* other values */
			printf("%s", lua_typename(L, t));
			break;

		}
		printf("  ");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

//http://www.lua.org/manual/5.3/manual.html#lua_CFunction
static int luaTestFunc(lua_State* state)
{
	/* number of arguments */
	int args = lua_gettop(state);

	for (int n = 1; n <= args; ++n) {
		printf("  arg %d: '%s'\n", n, lua_tostring(state, n));
	}

	lua_pushnumber(state, 123);
	return 1; /* number of results */
}

static int luaQuitGame(lua_State* state) {

	//    printf("luaQuitGame..\n");

	quit = true;

	return 0;
}

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

void Game::Run() {

	Entity player = { 0 };
	Console console = { false, "" };


	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);



	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow(
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

	//RESOURCES
	std::unordered_map<std::string, SDL_Surface*> spritesheets;

	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
	SDL_Surface *game = SDL_CreateRGBSurface(0, GAME_WIDTH, GAME_HEIGHT, 32, 0, 0, 0, 0);

	SDL_Surface *testSurface = SDL_LoadBMP("data/base/test.bmp");
	SDL_Surface *borderSurface = SDL_LoadBMP("data/base/borders/border.bmp");
	SDL_Surface *tile00Surface = SDL_LoadBMP("data/base/tiles/tile00.bmp");
	SDL_Surface *tile01Surface = SDL_LoadBMP("data/base/tiles/tile01.bmp");
	{
		std::string file = "data/base/spritesheets/player.bmp";
		spritesheets[file] = SDL_LoadBMP(file.c_str());
		player.surfaceStr = file;
	}
	SDL_Surface *bmpFont = SDL_LoadBMP("data/base/fonts/standard_font.bmp");

	SDL_Event e;

	//SDL_Rect pos = { 0,40,100,100 };

	//Lua
	lua_State *state = luaL_newstate();
	luaL_openlibs(state);

	lua_register(state, "luaTestFunc", luaTestFunc);

	//luaL_dostring(state, "io.write(\"luaTestFunc\")");
	//luaL_dostring(state, "luaTestFunc(\"First\", \"Second\", 112233)");

	//luaL_dostring(state, "io.write(\"ciao\")");

	/*
	lua_newtable(state);
	lua_setglobal(state, "game");

	lua_getglobal(state, "game");
	lua_pushstring(state, "system");
	lua_newtable(state);
	lua_settable(state, -3);
	lua_pop(state, -1);
	*/

	lua_newtable(state);
	lua_setglobal(state, "system");

	lua_getglobal(state, "system");
	lua_pushstring(state, "quit");
	lua_pushcfunction(state, luaQuitGame);
	lua_settable(state, -3);
	lua_pop(state, -1);

	//    luaL_dostring(state, "system.quit();");


	//    stackDump(state);

	if (luaL_dofile(state, "data/base/scripts/main.lua")) {
		SDL_ShowSimpleMessageBox(0, "ERRORL", lua_tostring(state, -1), window);
		// printf("Couldn't load file: %s\n", lua_tostring(state, -1));
		lua_pop(state, -1);

		stackDump(state);

		exit(1);
	}



	//Dungeon
	int tilesArray[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	int arrayWidth = 16;
	int arrayHeight = 9;

	SDL_StartTextInput();

	while (!quit)
	{

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.type == SDL_TEXTINPUT) {

				if (strcmp(e.text.text, "~") == 0) {
					console.visible = !console.visible;
				}


				//                printf("%s\n", e.text.text);

			}

			//Console
			if (console.visible == true) {

				if (e.type == SDL_KEYDOWN) {

					SDL_Keymod omar = SDL_GetModState();

					if (e.key.keysym.sym == SDLK_q) console.cmd = console.cmd + "q";
					if (e.key.keysym.sym == SDLK_w) console.cmd = console.cmd + "w";
					if (e.key.keysym.sym == SDLK_e) console.cmd = console.cmd + "e";
					if (e.key.keysym.sym == SDLK_r) console.cmd = console.cmd + "r";
					if (e.key.keysym.sym == SDLK_t) console.cmd = console.cmd + "t";
					if (e.key.keysym.sym == SDLK_y) console.cmd = console.cmd + "y";
					if (e.key.keysym.sym == SDLK_u) console.cmd = console.cmd + "u";
					if (e.key.keysym.sym == SDLK_i) console.cmd = console.cmd + "i";
					if (e.key.keysym.sym == SDLK_o) console.cmd = console.cmd + "o";
					if (e.key.keysym.sym == SDLK_p) console.cmd = console.cmd + "p";
					if (e.key.keysym.sym == SDLK_a) console.cmd = console.cmd + "a";
					if (e.key.keysym.sym == SDLK_s) console.cmd = console.cmd + "s";
					if (e.key.keysym.sym == SDLK_d) console.cmd = console.cmd + "d";
					if (e.key.keysym.sym == SDLK_f) console.cmd = console.cmd + "f";
					if (e.key.keysym.sym == SDLK_h) console.cmd = console.cmd + "h";
					if (e.key.keysym.sym == SDLK_j) console.cmd = console.cmd + "j";
					if (e.key.keysym.sym == SDLK_k) console.cmd = console.cmd + "k";
					if (e.key.keysym.sym == SDLK_l) console.cmd = console.cmd + "l";
					if (e.key.keysym.sym == SDLK_z) console.cmd = console.cmd + "z";
					if (e.key.keysym.sym == SDLK_x) console.cmd = console.cmd + "x";
					if (e.key.keysym.sym == SDLK_c) console.cmd = console.cmd + "c";
					if (e.key.keysym.sym == SDLK_v) console.cmd = console.cmd + "v";
					if (e.key.keysym.sym == SDLK_b) console.cmd = console.cmd + "b";
					if (e.key.keysym.sym == SDLK_n) console.cmd = console.cmd + "n";
					if (e.key.keysym.sym == SDLK_m) console.cmd = console.cmd + "m";

					if (e.key.keysym.sym == SDLK_PERIOD) console.cmd = console.cmd + ".";
					if (e.key.keysym.sym == SDLK_SEMICOLON) console.cmd = console.cmd + ";";

					if (e.key.keysym.sym == SDLK_QUOTE) {
						if (e.key.keysym.sym == SDLK_QUOTE && omar & KMOD_SHIFT) {
							console.cmd = console.cmd + "\"";
						}
						else {
							console.cmd = console.cmd + "'";

						}
					}

					if (e.key.keysym.sym == SDLK_9) {
						if (e.key.keysym.sym == SDLK_9 && omar & KMOD_SHIFT) {
							console.cmd = console.cmd + "(";
						}
						else {
							console.cmd = console.cmd + "9";

						}
					}

					if (e.key.keysym.sym == SDLK_0) {
						if (e.key.keysym.sym == SDLK_0 && omar & KMOD_SHIFT) {
							console.cmd = console.cmd + ")";
						}
						else {
							console.cmd = console.cmd + "0";
						}
					}
					if (e.key.keysym.sym == SDLK_SPACE) console.cmd = console.cmd + " ";
					if (e.key.keysym.sym == SDLK_BACKSPACE) console.cmd = console.cmd.substr(0, console.cmd.length() - 1);

				}

				//printf("console: %s\n", console.cmd.c_str());

				if (e.type == SDL_KEYDOWN) {

					//					if (e.key.keysym.sym == SDLK_BACKQUOTE) {
					//						console.visible = !console.visible;
					//					}

					if (e.key.keysym.sym == SDLK_RETURN) {
						luaL_dostring(state, console.cmd.c_str());
						console.cmd = "";

					}
				}

			}
			else {

				const Uint8 *state = SDL_GetKeyboardState(NULL);




				if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.sym == SDLK_BACKQUOTE) {
						console.visible = !console.visible;
					}
				}

				if (state[SDL_SCANCODE_LEFT]) {

					//int oldPos = playerPos;

					int x = player.pos % arrayWidth;
					int y = (player.pos / arrayWidth) % arrayHeight;

					x -= 1;

					player.pos = x + arrayWidth*y;
				}
				else

					if (state[SDL_SCANCODE_RIGHT]) {

						int x = player.pos % arrayWidth;
						int y = (player.pos / arrayWidth) % arrayHeight;

						x += 1;

						player.pos = x + arrayWidth*y;
					}
					else

						if (state[SDL_SCANCODE_UP]) {

							int x = player.pos % arrayWidth;
							int y = (player.pos / arrayWidth) % arrayHeight;

							y -= 1;

							player.pos = x + arrayWidth*y;
						}
						else

							if (state[SDL_SCANCODE_DOWN]) {

								int x = player.pos % arrayWidth;
								int y = (player.pos / arrayWidth) % arrayHeight;

								y += 1;

								player.pos = x + arrayWidth*y;
							}
			}

		}

		//clear screen surface
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 0));
		SDL_FillRect(game, NULL, SDL_MapRGB(screen->format, 0, 255, 0));

		//render tiles
		for (size_t i = 0; i < arrayWidth * arrayHeight; i++)
		{
			int x = i % arrayWidth;
			int y = (i / arrayWidth) % arrayHeight;

			SDL_Rect pos = { x * 16, y * 16, 16, 16 };

			//printf("x: %i , y: %i\n", x, y);

			if (tilesArray[i] == 0) {

				SDL_BlitSurface(tile00Surface, NULL, game, &pos);
			}
			else

				if (tilesArray[i] == 1) {

					SDL_BlitSurface(tile01Surface, NULL, game, &pos);
				}
		}


		//render player
		{

			int x = player.pos % arrayWidth;
			int y = (player.pos / arrayWidth) % arrayHeight;

			//Player-->Game
			SDL_Rect pos = { x * 16, y * 16, 16, 16 };
			SDL_BlitSurface(spritesheets[player.surfaceStr], NULL, game, &pos);
		}


		//SDL_BlitSurface(testSurface, 0, game, NULL);

		//Border-->Screen
		SDL_BlitSurface(borderSurface, 0, screen, 0);

		//TextBox-->Game
		SDL_BlitSurface(bmpFont, 0, screen, 0);
		renderText("TEXT MESSAGE BOX\nHello World!", bmpFont, game);

		//Game-->Screen
		SDL_Rect location = { 72,40,100,100 };
		SDL_BlitSurface(game, 0, screen, &location);

		//Console-->Screen
		{
			if (console.visible) {
				SDL_Surface *consoleSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT - 16, 32, 0, 0, 0, 0);
				SDL_FillRect(consoleSurface, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

				renderTextLine(">" + console.cmd, 0, 24, bmpFont, consoleSurface);

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

	lua_close(state);

	SDL_FreeSurface(testSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();

}
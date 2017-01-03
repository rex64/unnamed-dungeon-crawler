#include "Game.h"

#ifdef __APPLE__

#include <SDL2/SDL.h>

#elif _WIN32

#include <SDL.h>
#include <stdio.h>
#include <cstring>

#endif

#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "res/ResourceManager.h"
#include "stage/StageManager.h"
#include "ScriptManager.h"
#include "Console.h"
#include "RenderManager.h"
#include "ui/MenuManager.h"
#include "save/SaveManager.h"

Game* Game::game;

Game::Game()
{
}


Game::~Game()
{
}

void Game::init() {

	game = this;

	//SDL initialization
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "We compiled against SDL version %d.%d.%d ...\n", compiled.major, compiled.minor, compiled.patch);
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "We are linking against SDL version %d.%d.%d.\n", linked.major, linked.minor, linked.patch);

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"unamed-dungeon-crawler",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH * 2,
		SCREEN_HEIGHT * 2,
		SDL_WINDOW_RESIZABLE
	);

	//managers initialization
	ResourceManager *resManager = new ResourceManager();
	resManager->init();

	Console *console = new Console();
	console->init();

	ScriptManager *scriptManager = new ScriptManager();
	scriptManager->init();

	StageManager *stageManager = new StageManager();
	stageManager->init();

	RenderManager *renderManager = new RenderManager();
	renderManager->init();

	MenuManager *menuManager = new MenuManager();
	menuManager->init();

	SaveManager *saveManager = new SaveManager();
	saveManager->init();

	resManager->loadDataFolder();

	inputEnabled = true;
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

	SDL_Event e;

	SDL_StartTextInput();

	m_bQuit = false;

	ScriptManager::manager->runMain();

	SDL_AddTimer(260, my_callbackfunc, 0);

	Buttons b_lastFrame = { false };

	SDL_Scancode UP		= SDL_SCANCODE_UP;
	SDL_Scancode RIGHT	= SDL_SCANCODE_RIGHT;
	SDL_Scancode DOWN	= SDL_SCANCODE_DOWN;
	SDL_Scancode LEFT	= SDL_SCANCODE_LEFT;
	SDL_Scancode OK		= SDL_SCANCODE_X;
	SDL_Scancode CANCEL = SDL_SCANCODE_Z;
	SDL_Scancode MENU	= SDL_SCANCODE_TAB;
	SDL_Scancode PAUSE  = SDL_SCANCODE_RETURN;

	while (!m_bQuit)
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		Buttons buttons = { false };
		buttons.up = state[UP];
		buttons.right = state[RIGHT];
		buttons.down = state[DOWN];
		buttons.left = state[LEFT];
		buttons.ok = state[OK];
		buttons.cancel = state[CANCEL];
		buttons.menu = state[MENU];
		buttons.pause = state[PAUSE];

		while (SDL_PollEvent(&e) != 0)
		{

			const Uint8 *state = SDL_GetKeyboardState(NULL);

			Buttons buttons = { false };
			buttons.up = state[UP];
			buttons.right = state[RIGHT];
			buttons.down = state[DOWN];
			buttons.left = state[LEFT];
			buttons.ok = state[OK];
			buttons.cancel = state[CANCEL];
			buttons.menu = state[MENU];
			buttons.pause = state[PAUSE];

			if (e.type == SDL_KEYDOWN) {

				if (inputEnabled) {
					ScriptManager::manager->onInputGame(buttons, b_lastFrame);
				}
			}
			if (e.type == SDL_TEXTINPUT) {

				if (strcmp(e.text.text, "~") == 0) {
					Console::Console::console->visible = !Console::console->visible;
				}

			}

			if (e.type == SDL_QUIT)
			{
				m_bQuit = true;
			}


		}

		ScriptManager::manager->updateGame(16);
		RenderManager::manager->render();
		checkIfStackIsEmpty(ScriptManager::manager->m_L);
		b_lastFrame = buttons;
		SDL_Delay(16);

	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Quitting..");

	ScriptManager::manager->onQuit();

	//SDL_FreeSurface(testSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

void Game::showMsgBox(std::string msg)
{
	showMsgBox(msg.c_str());
}

void Game::showMsgBox(const char *msg)
{
	SDL_ShowSimpleMessageBox(0, "READ CAREFULLY", msg, window);
	printf("[showMsgBox] %s\n", msg);
}

int Game_enableInput(lua_State *L) {

	Game::game->inputEnabled = true;

	return 0;
}

int Game_disableInput(lua_State *L) {

	Game::game->inputEnabled = false;

	return 0;
}

int Game_quitGame(lua_State *L) {

	SDL_Event user_event;

	user_event.type = SDL_QUIT;
	/*user_event.user.code = 2;
	user_event.user.data1 = NULL;
	user_event.user.data2 = NULL;*/
	SDL_PushEvent(&user_event);

	return 0;
}

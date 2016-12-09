#include "Game.h"

#ifdef __APPLE__

#include <SDL2/SDL.h>

#elif _WIN32

#include <SDL.h>
#include <stdio.h>

#endif

#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "res/ResourceManager.h"
#include "stage/StageManager.h"
#include "ScriptManager.h"
#include "Console.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ui\MenuManager.h"
#include "SaveManager.h"

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

	InputManager *inputManger = new InputManager();
	inputManger->init();

	RenderManager *renderManager = new RenderManager();
	renderManager->init();

	MenuManager *menuManager = new MenuManager();
	menuManager->init();

	SaveManager *saveManager = new SaveManager();
	saveManager->init();

	resManager->loadDataFolder();
	
	inputManger->registerInput(menuManager);
	inputManger->registerInput(console);
	inputManger->registerInput(stageManager);
	inputManger->registerInput(stageManager);
	inputManger->registerInput(scriptManager);

	//Register input handlers

	//Register renderer

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

	//fake setup -------- start
	StageManager::manager->currStage = new Stage();
	StageManager::manager->currStage->load("base.dungeons.dungeon1", 0);
	
	Equip *sword = new Equip();
	sword->addSkill("base.skills.skilltest1");
	sword->addSkill("base.skills.sword_attack");
	Hero *tank = new Hero("base.heroes.tank");
	tank->addEquip(sword);

	Equip *staff = new Equip();
	staff->addSkill("base.skills.skilltest1");
	staff->addSkill("base.skills.magic_blast");
	Hero *heals = new Hero("base.heroes.heals");
	heals->addEquip(staff);

	Equip *knife = new Equip();
	knife->addSkill("base.skills.skilltest1");
	knife->addSkill("base.skills.mega_hit");
	Hero *melee = new Hero("base.heroes.melee");
	melee->addEquip(sword);

	Equip *bow = new Equip();
	bow->addSkill("base.skills.skilltest1");
	bow->addSkill("base.skills.magic_arrow");
	Hero *ranged = new Hero("base.heroes.ranged");
	ranged->addEquip(bow);

	SaveManager::manager->manager->addHero(tank);
	SaveManager::manager->manager->addHero(heals);
	SaveManager::manager->manager->addHero(melee);
	SaveManager::manager->manager->addHero(ranged);

	//fake setup -------- end

	SDL_AddTimer(260, my_callbackfunc, 0);

	//MenuManager::manager->addSelectWindow();

	while (!m_bQuit)
	{

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN) {
				InputManager::manager->onInput(&e);
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

		if (ScriptManager::manager->weBattle()) {
		
			ScriptManager::manager->doString("battle.update()");
		}

		RenderManager::manager->render();
		checkIfStackIsEmpty(ScriptManager::manager->m_L);
		SDL_Delay(16);
		
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Quitting..");

	ScriptManager::manager->onQuit();

	

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

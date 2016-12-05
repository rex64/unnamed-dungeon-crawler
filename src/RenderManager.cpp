#include "RenderManager.h"
#include "IRenderable.h"
#include "Game.h"
#include "Console.h"
#include "stage/StageManager.h"
#include "res/ResourceManager.h"
#include "ui/MenuManager.h"
#include "ScriptManager.h"

#ifdef __APPLE__
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#elif _WIN32
#include <lua.hpp>
#endif

RenderManager* RenderManager::manager;

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

void RenderManager::init()
{

	manager = this;

	renderer = SDL_CreateRenderer(Game::game->window, -1, 0);


	texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	//    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	//    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH*4, SCREEN_HEIGHT*4);

	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", SDL_GetError(), window);

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
	game = SDL_CreateRGBSurface(0, GAME_WIDTH, GAME_HEIGHT, 32, 0, 0, 0, 0);	

}

void RenderManager::renderWindow(SDL_Rect rect) {


	SDL_Surface *bmp = ResourceManager::manager->getSprite("base.menus.menu-window-border");

	SDL_Rect srcRect = SDL_Rect{ 0 , 0, 8, 8 };

	for (int y = 0; y < rect.h + 1; y++) {

		if (y == 0) srcRect.y = 0;
		else if (y == rect.h) srcRect.y = 16;
		else srcRect.y = 8;

		for (int x = 0; x < rect.w + 1; x++) {

			if (x == 0) srcRect.x = 0;
			else if (x == rect.w) srcRect.x = 16;
			else srcRect.x = 8;

			SDL_Rect dstRect = SDL_Rect{ rect.x + (8 * x), rect.y + (8 * y), 8 , 8 };

			SDL_BlitSurface(bmp, &srcRect, game, &dstRect);

		}

	}

}

void RenderManager::renderMenuItem(std::string str, int x, int y) {

	renderTextLine1(str, x, y, ResourceManager::manager->getFont("base.fonts.standard_font"), game);

}

void RenderManager::render()
{
	//clear screen surface
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 0));
	SDL_FillRect(game, NULL, SDL_MapRGB(screen->format, 0, 255, 0));

	for (IRenderable *i : renderStack) {
		i->onRender();
	}

	int cameraOffsetX = 0;
	int cameraOffsetY = 0;

	if (Entity *player = StageManager::manager->currStage->player) {
	
		Point playerPos = StageManager::manager->currStage->toXY(player->tileId);

		cameraOffsetX = (-16 * playerPos.x) + (16*7);
		cameraOffsetY = (-16 * playerPos.y) + (16*4);
	}

	//render tiles
	for (size_t i = 0; i < StageManager::manager->currStage->arrayWidth * StageManager::manager->currStage->arrayHeight; i++)
	{
		int x = i % StageManager::manager->currStage->arrayWidth;
		int y = (i / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

		

		SDL_Rect pos = { x * 16 + cameraOffsetX, y * 16 + cameraOffsetY, 16, 16 };

		SDL_BlitSurface(
			ResourceManager::manager->getTile(StageManager::manager->currStage->getTile(i).tileResID),
			NULL,
			game,
			&pos
		);
	}

	//render player
	//{
	//	Entity *player = StageManager::manager->currStage->player;
	//	int x = player->tileId % StageManager::manager->currStage->arrayWidth;
	//	int y = (player->tileId / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

	//	//Player-->Game
	//	SDL_Rect pos = { x * 16, y * 16, 16, 16 };
	//	SDL_BlitSurface(ResourceManager::manager->getSprite(player->entityResID), NULL, game, &pos);
	//}

	for (auto kv : StageManager::manager->currStage->entities) {
	
		if (Entity *entity = kv.second) {

			int x = entity->tileId % StageManager::manager->currStage->arrayWidth;
			int y = (entity->tileId / StageManager::manager->currStage->arrayWidth) % StageManager::manager->currStage->arrayHeight;

			//Player-->Game
			SDL_Rect pos = { x * 16 + cameraOffsetX, y * 16 + cameraOffsetY, 16, 16 };
			SDL_Rect rez{ 0 + (16 * entity->facing),0 (16 * entity->facing),16,16 };

			std::string spriteID = ((FieldEntityData*)(ResourceManager::manager->entityDatas[entity->entityDataID]->data))->spritesheet;

			SDL_BlitSurface(ResourceManager::manager->getSprite(spriteID), &rez, game, &pos);
			
		};
	}


	//SDL_BlitSurface(testSurface, 0, game, NULL);

	//Border-->Screen
	SDL_BlitSurface(ResourceManager::manager->getBorder("base.borders.border"), 0, screen, 0);

	//TextBox-->Game
	//SDL_BlitSurface(ResourceManager::manager->fonts["base.fonts.standard_font"], 0, screen, 0);
	//renderText("TEXT MESSAGE BOX\nHello World!", ResourceManager::manager->fonts["base.fonts.standard_font"], game);

	//Menu-->Game
	/*
	SDL_BlitSurface(ResourceManager::manager->getFont("base.fonts.standard_font"), 0, screen, 0);
	renderText("TEXT MESSAGE BOX\nHello World!", ResourceManager::manager->getFont("base.fonts.standard_font"), game);
	*/

	ScriptManager::manager->doString("ui.render()"); //TODO: lol


	//Game-->Screen
	SDL_Rect location = { 72,40,100,100 };
	SDL_BlitSurface(game, 0, screen, &location);

	//Console-->Screen
	{
		if (Console::console->visible) {
			SDL_Surface *consoleSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT - 16, 32, 0, 0, 0, 0);
			SDL_FillRect(consoleSurface, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

			renderTextLine(">" + Console::console->cmd, 0, 24, ResourceManager::manager->getFont("base.fonts.standard_font"), consoleSurface);

			SDL_BlitSurface(consoleSurface, 0, screen, 0);
			SDL_FreeSurface(consoleSurface);
		}
	}

	SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, 0, 0);
	SDL_RenderPresent(renderer);
}

//void RenderManager::registerRenderable(IRenderable *)
//{
//
//}


void renderTextLine(std::string str, int x, int y, FontData* fontData, SDL_Surface* surf) {

	if (Console::console->showCursor) {
		str = str + '_';
	}

	int i = 0;
	for (char& c : str) {

		int charIndex = c - 32;
		SDL_Rect src = { 8 * charIndex, 0, 8, 8 };
		SDL_Rect dst = { (8 + x) * i, y * 8 , 8, 8 };

		SDL_BlitSurface(fontData->fontSurf, &src, surf, &dst);
		++i;
	}
}

void renderTextLine1(std::string str, int x, int y, FontData* fontData, SDL_Surface* surf) {

	int i = 0;
	for (char& c : str) {

		int charIndex = c - 32;
		SDL_Rect src = { fontData->charWidth * charIndex, 0, fontData->charWidth, fontData->charHeight };
		SDL_Rect dst = { (fontData->charWidth * i) + x, y, fontData->charWidth, fontData->charHeight };

		SDL_BlitSurface(fontData->fontSurf, &src, surf, &dst);
		++i;
	}
}

void renderText(std::string str, FontData* fontData, SDL_Surface* surf) {

	int i = 0;
	int j = 0;
	for (char& c : str) {
		if (((int)c) == 10) {
			++j;
			i = 0;
			continue;
		};
		int charIndex = c - 32;
		SDL_Rect src = { 8 * charIndex, 0, 8, 8 };
		SDL_Rect dst = { 8 * i, (14 + j) * 8 , 8, 8 };

		SDL_BlitSurface(fontData->fontSurf, &src, surf, &dst);
		++i;
	}
}

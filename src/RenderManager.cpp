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
	uiSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

	initPalette();
}

void RenderManager::initPalette() {

	SDL_Color colors[5];

	//Chroma Key
	colors[0].r = (Uint8)250;
	colors[0].g = (Uint8)0;
	colors[0].b = (Uint8)250;

	//Color 1
	colors[1].r = (Uint8)246;
	colors[1].g = (Uint8)245;
	colors[1].b = (Uint8)149;

	//Color 2
	colors[2].r = (Uint8)140;
	colors[2].g = (Uint8)173;
	colors[2].b = (Uint8)15;

	//Color 3
	colors[3].r = (Uint8)48;
	colors[3].g = (Uint8)98;
	colors[3].b = (Uint8)48;

	//Color 4
	colors[4].r = (Uint8)15;
	colors[4].g = (Uint8)56;
	colors[4].b = (Uint8)15;

	palette = SDL_AllocPalette(256);
	format = SDL_AllocFormat(SDL_PIXELFORMAT_INDEX8);
	SDL_SetPaletteColors(palette, colors, 0, 5);
	SDL_SetPixelFormatPalette(format, palette);

}

SDL_Surface* RenderManager::invertPixels(std::string resId, SDL_Surface *surf) {

	SDL_Surface *surfRet = SDL_ConvertSurface(surf, surf->format, 0);

	SDL_LockSurface(surf);

	SDL_LockSurface(surfRet);

	for (int y = 0; y < surf->h; y++) {
	
		for (int x = 0; x < surf->w; x++) {
		
			int bpp = surf->format->BytesPerPixel;
			*(((Uint8 *)surfRet->pixels + y * surfRet->pitch + x * bpp) + 0) = ~*(((Uint8 *)surf->pixels + y * surf->pitch + x * bpp) + 0);
			*(((Uint8 *)surfRet->pixels + y * surfRet->pitch + x * bpp) + 1) = ~*(((Uint8 *)surf->pixels + y * surf->pitch + x * bpp) + 1);
			*(((Uint8 *)surfRet->pixels + y * surfRet->pitch + x * bpp) + 2) = ~*(((Uint8 *)surf->pixels + y * surf->pitch + x * bpp) + 2);
		}
	}

	SDL_UnlockSurface(surfRet);
	SDL_UnlockSurface(surf);


	return surfRet;
}

SDL_Surface* RenderManager::convertRGBtoIndexed(std::string resId, SDL_Surface *surf) {

	SDL_Surface *surfRet = SDL_ConvertSurface(surf, this->format, 0);

	int i = 0;

	for (int y = 0; y < surf->h; y++) {

		for (int x = 0; x < surf->w; x++) {
		
		
			int bpp = surf->format->BytesPerPixel;
			Uint8 r = *(((Uint8 *)surf->pixels + y * surf->pitch + x * bpp) + 0);
			Uint8 g = *(((Uint8 *)surf->pixels + y * surf->pitch + x * bpp) + 1);
			Uint8 b = *(((Uint8 *)surf->pixels + y * surf->pitch + x * bpp) + 2);


			Uint8 value = -1;

			if ((r == 250) && (g == 0) && (b == 250)) {
				value = 0;
			}
			else if ((r == 255) && (g == 255) && (b == 255)) {
					value = 1;
				}else if ((r == 185) && (g == 185) && (b == 185)) {
						value = 2;

					} else if ((r == 105) && (g == 105) && (b == 105)) {

							value = 3;

						} else if ((r == 0) && (g == 0) && (b == 0)) {
								value = 4;
							} else {

								Game::game->showMsgBox((resId + " RGB error").c_str());

							}

						int bpp2 = surfRet->format->BytesPerPixel;
						*(((Uint8 *)surfRet->pixels + y * surfRet->pitch + x * bpp2) + 0) = value;

		}
	}
	SDL_SetColorKey(surfRet, 1, SDL_MapRGB(surfRet->format, 250, 0, 250));


	return surfRet;

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

			SDL_BlitSurface(bmp, &srcRect, uiSurface, &dstRect);

		}

	}

}

void RenderManager::renderTextLine(std::string str, int x, int y, bool inverted) {

	renderTextLine1(
		str, 
		x, y, 
		ResourceManager::manager->getFont("base.fonts.standard_font"), 
		RenderManager::manager->uiSurface, 
		inverted
	);

}

void RenderManager::renderSprite(std::string str, int x, int y) {

	SDL_Surface *surf = ResourceManager::manager->getSprite(str);

	SDL_Rect dstRect = SDL_Rect{ x, y, 0 , 0 };


	SDL_BlitSurface(surf, 0, uiSurface, &dstRect);
	

}

void RenderManager::render()
{
	//clear screen surface
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 250, 0, 250));
	SDL_FillRect(game, NULL, SDL_MapRGB(game->format, 250, 0, 250));
	SDL_FillRect(uiSurface, NULL, SDL_MapRGB(uiSurface->format, 250, 0, 250));
	SDL_SetColorKey(uiSurface, 1, SDL_MapRGB(uiSurface->format, 250, 0, 250));

	ScriptManager::manager->doString("game.render()"); //TODO: fix

	/*for (IRenderable *i : renderStack) {
		i->onRender();
	}*/

	//SDL_BlitSurface(testSurface, 0, game, NULL);

	//Border-->Screen
	SDL_BlitSurface(ResourceManager::manager->getBorder("base.borders.border"), 0, screen, 0);

	//Game-->Screen
	SDL_Rect location = { 72,40,100,100 };
	SDL_BlitSurface(game, 0, screen, &location);

	//UI-->Screen
	SDL_BlitSurface(uiSurface, 0, screen, 0);

	//Console-->Screen
	{
		if (Console::console->visible) {
			SDL_Surface *consoleSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT - 16, 32, 0, 0, 0, 0);
			SDL_FillRect(consoleSurface, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

			//TODO: fix
			//renderTextLine(">" + Console::console->cmd, 0, 24, ResourceManager::manager->getFont("base.fonts.standard_font"), consoleSurface);

			SDL_BlitSurface(consoleSurface, 0, screen, 0);
			SDL_FreeSurface(consoleSurface);
		}
	}

	SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, 0, 0);
	SDL_RenderPresent(renderer);
}

void renderTextLine1(std::string str, int x, int y, FontData* fontData, SDL_Surface* surf, bool inverted) {

	int i = 0;
	int cursor = 0;
	for (char& c : str) {

		CharData *charData = fontData->chars[std::string(1, c)];

		if (charData == nullptr) {
			Game::game->showMsgBox((std::string("character not found: ") + c).c_str());
			throw std::exception(":(");
		}

		SDL_Surface *charSurf = inverted ? 
			fontData->chars[std::string(1, c)]->surfInverted : fontData->chars[std::string(1, c)]->surfNormal;

		SDL_Rect src = { 0, 0, charSurf->w, charSurf->h};
		SDL_Rect dst = { cursor + x, y, charSurf->w, charSurf->h };

		cursor = cursor + charData->width + 1;

		
		SDL_BlitSurface(charSurf, &src, surf, &dst);
		++i;
	}
}

int Render_renderTile(lua_State *L) {

	std::string spriteID = lua_tostring(L, 1);
	int x = lua_tointeger(L, 2);
	int y = lua_tointeger(L, 3);

	SDL_Rect pos = { x, y, 16, 16 };

	SDL_BlitSurface(
		ResourceManager::manager->getSprite(spriteID), 
		nullptr, 
		RenderManager::manager->game, 
		&pos);

	return 0;
}

int Render_renderSpriteSheet(lua_State *L) {

	std::string spriteID = lua_tostring(L, 1);
	int x = lua_tointeger(L, 2);
	int y = lua_tointeger(L, 3);
	int facing = lua_tointeger(L, 4);

	SDL_Rect posRect	= { x, y, 16, 16 };
	SDL_Rect facingRect = { 16 * facing, 0, 16, 16 };
	SDL_BlitSurface(
		ResourceManager::manager->getSprite(spriteID),
		&facingRect,
		RenderManager::manager->game,
		&posRect);


	return 0;
}

int Render_renderSprite(lua_State *L) {

	std::string spriteID = lua_tostring(L, 1);
	int x = lua_tointeger(L, 2);
	int y = lua_tointeger(L, 3);

	SDL_Rect posRect = { x, y, 16, 16 };

	SDL_BlitSurface(
		ResourceManager::manager->getSprite(spriteID),
		0,
		RenderManager::manager->game,
		&posRect);


	return 0;
}
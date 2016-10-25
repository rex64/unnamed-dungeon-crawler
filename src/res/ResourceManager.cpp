#include "ResourceManager.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

ResourceManager* ResourceManager::manager;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::init() {

	manager = this;

	//RESOURCES
	
	//SDL_Surface *testSurface = SDL_LoadBMP("data/base/test.bmp");
	
	SDL_Surface *borderSurface = SDL_LoadBMP("data/base/borders/border.bmp");
	borders["data.base.borders.border"] = borderSurface;
	
	SDL_Surface *tile00Surface = SDL_LoadBMP("data/base/tiles/tile00.bmp");
	tiles["data.base.tiles.tile00"] = tile00Surface;
	
	SDL_Surface *tile01Surface = SDL_LoadBMP("data/base/tiles/tile01.bmp");
	tiles["data.base.tiles.tile01"] = tile01Surface;

	spritesheets["data.base.spritesheets.player"] = SDL_LoadBMP("data/base/spritesheets/player.bmp");

	SDL_Surface *bmpFont = SDL_LoadBMP("data/base/fonts/standard_font.bmp");
	fonts["data.base.fonts.standard_font"] = bmpFont;

}
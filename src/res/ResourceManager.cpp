#include "ResourceManager.h"
#include "../Game.h"


#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <algorithm>

ResourceManager* ResourceManager::manager;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::init() {

	manager = this;

	//Load Defaults
	#include "default_sprite.c"

	//stolen from https://caedesnotes.wordpress.com/2015/04/13/how-to-integrate-your-sdl2-window-icon-or-any-image-into-your-executable/
	// these masks are needed to tell SDL_CreateRGBSurface(From)
	// to assume the data it gets is byte-wise RGB(A) data
	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		int shift = (my_icon.bytes_per_pixel == 3) ? 8 : 0;
		rmask = 0xff000000 >> shift;
		gmask = 0x00ff0000 >> shift;
		bmask = 0x0000ff00 >> shift;
		amask = 0x000000ff >> shift;
	#else // little endian, like x86
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = (default_sprite.bytes_per_pixel == 3) ? 0 : 0xff000000;
	#endif

	spriteDefault = SDL_CreateRGBSurfaceFrom(
		(void*)default_sprite.pixel_data, 
		default_sprite.width,
		default_sprite.height, 
		default_sprite.bytes_per_pixel*8, 
		default_sprite.bytes_per_pixel*default_sprite.width,
		rmask, 
		gmask, 
		bmask, 
		amask
	);

	//RESOURCES
	
	//SDL_Surface *testSurface = SDL_LoadBMP("data/base/test.bmp");
	
	loadBorder("data/base/borders/border.bmp");
	
	loadTile("data/base/tiles/tile00.bmp");
	
	loadTile("data/base/tiles/tile01.bmp");

	loadSprite("data/base/spritesheets/player.bmp");
	loadSprite("data/base/spritesheets/enemy.bmp");
	loadSprite("data/base/spritesheets/stairs.bmp");

	loadFont("data/base/fonts/standard_font.bmp");

	SDL_Surface* tre =  getSprite("omar");

}

void ResourceManager::loadSprite(std::string f) {

	if (SDL_Surface *surf = SDL_LoadBMP(f.c_str())) {

		std::string resID = f.substr(0, f.size() -4);
		std::replace(resID.begin(), resID.end(), '/', '.');
		
		spritesheets[resID] = surf;

	}
	else
	{
		Game::game->showMsgBox(SDL_GetError());
	}

}
void ResourceManager::loadTile(std::string f) {

	if (SDL_Surface *surf = SDL_LoadBMP(f.c_str())) {

		std::string resID = f.substr(0, f.size() - 4);
		std::replace(resID.begin(), resID.end(), '/', '.');

		tiles[resID] = surf;

	}
	else
	{
		Game::game->showMsgBox(SDL_GetError());
	}
}
void ResourceManager::loadFont(std::string f) {

	if (SDL_Surface *surf = SDL_LoadBMP(f.c_str())) {

		std::string resID = f.substr(0, f.size() - 4);
		std::replace(resID.begin(), resID.end(), '/', '.');

		fonts[resID] = surf;

	}
	else
	{
		Game::game->showMsgBox(SDL_GetError());
	}
}
void ResourceManager::loadBorder(std::string f) {

	if (SDL_Surface *surf = SDL_LoadBMP(f.c_str())) {

		std::string resID = f.substr(0, f.size() - 4);
		std::replace(resID.begin(), resID.end(), '/', '.');

		borders[resID] = surf;

	}
	else
	{
		Game::game->showMsgBox(SDL_GetError());
	}
}

SDL_Surface* ResourceManager::getSprite(std::string id) { 
	
	SDL_Surface* ret = spritesheets[id];

	if (ret == nullptr) {
		return spriteDefault;
	}

	return ret;
}
SDL_Surface* ResourceManager::getTile(std::string id) {

	SDL_Surface* ret = tiles[id];

	if (ret == nullptr) {
		return spriteDefault;
	}

	return ret;
}
SDL_Surface* ResourceManager::getFont(std::string id) {

	SDL_Surface* ret = fonts[id];

	if (ret == nullptr) {
		return spriteDefault;
	}

	return ret;
}
SDL_Surface* ResourceManager::getBorder(std::string id) {

	SDL_Surface* ret = borders[id];

	if (ret == nullptr) {
		return spriteDefault;
	}

	return ret;
}
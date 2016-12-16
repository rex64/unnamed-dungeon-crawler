#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#ifdef __APPLE__
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#elif _WIN32
#include <lua.hpp>
#endif

#include <vector>
#include <string>

class IRenderable;
class FontData;

class RenderManager
{

public:
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *screen;
	SDL_Surface *game;
	SDL_Surface *uiSurface;

public:
	RenderManager();
	~RenderManager();

	void init();
	void render();
	void renderWindow(SDL_Rect rect);
	void renderMenuItem(std::string str, int x, int y);
	void renderSprite(std::string str, int x, int y);
	static RenderManager *manager;

	std::vector<IRenderable*> renderStack;
	//void registerRenderable(IRenderable*);

};

extern "C" void renderText(std::string str, FontData* fontData, SDL_Surface* surf);
extern "C" void renderTextLine(std::string str, int x, int y, FontData* fontData, SDL_Surface* surf);
extern "C" void renderTextLine1(std::string str, int x, int y, FontData* fontData, SDL_Surface* surf);

extern "C" {


	int Render_renderTile(lua_State *L);
	int Render_renderSprite(lua_State *L);

}

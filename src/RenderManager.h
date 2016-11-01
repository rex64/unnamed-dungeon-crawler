#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <vector>

class IRenderable;

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	void init();
	void render();
	static RenderManager *manager;

	std::vector<IRenderable*> renderStack;
	void registerRenderable(IRenderable*);

	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *screen;
	SDL_Surface *game;

};

extern "C" void renderText(std::string str, SDL_Surface* charSet, SDL_Surface* surf);
extern "C" void renderTextLine(std::string str, int x, int y, SDL_Surface* charSet, SDL_Surface* surf);

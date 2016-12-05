#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <vector>

class IRenderable;
class FontData;

class RenderManager
{

public:
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *screen;
	SDL_Surface *game;

public:
	RenderManager();
	~RenderManager();

	void init();
	void render();
	void renderWindow(SDL_Rect rect);
	void renderMenuItem(std::string str, int x, int y);
	static RenderManager *manager;

	std::vector<IRenderable*> renderStack;
	//void registerRenderable(IRenderable*);

};

extern "C" void renderText(std::string str, FontData* fontData, SDL_Surface* surf);
extern "C" void renderTextLine(std::string str, int x, int y, FontData* fontData, SDL_Surface* surf);
extern "C" void renderTextLine1(std::string str, int x, int y, FontData* fontData, SDL_Surface* surf);

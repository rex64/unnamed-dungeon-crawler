#pragma once

#include <string>

struct SDL_Surface;

struct CharData {

	std::string charz;
	std::string fileName;
	int width;
	SDL_Surface *surfNormal;
	SDL_Surface *surfInverted;

};
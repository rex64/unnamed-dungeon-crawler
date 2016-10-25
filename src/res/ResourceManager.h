#pragma once

#include <unordered_map>

class SDL_Surface;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void init();

	static ResourceManager *manager;

	std::unordered_map<std::string, SDL_Surface*> spritesheets;
	std::unordered_map<std::string, SDL_Surface*> tiles;
	std::unordered_map<std::string, SDL_Surface*> fonts;
	std::unordered_map<std::string, SDL_Surface*> borders;

private:
	
};

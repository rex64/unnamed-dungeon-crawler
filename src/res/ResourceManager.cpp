#include "ResourceManager.h"
#include "../Game.h"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <algorithm>
#include <tinydir.h>
#include "tinyxml2.h"
#include "../ScriptManager.h"

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

	loadFont("data/base/fonts/standard_font.bmp");

	//SDL_Surface* tre =  getSprite("omar");

}

void ResourceManager::loadSprite(std::string resId, std::string filePath) {

	if (SDL_Surface *surf = SDL_LoadBMP(filePath.c_str())) {

		spritesheets[resId] = surf;
		SDL_Log("Loaded %s", resId.c_str());

	}
	else
	{
		Game::game->showMsgBox(SDL_GetError());
	}

}

//void ResourceManager::loadSprite(std::string f) {
//
//	if (SDL_Surface *surf = SDL_LoadBMP(f.c_str())) {
//
//		std::string resID = f.substr(0, f.size() -4);
//		std::replace(resID.begin(), resID.end(), '/', '.');
//		
//		spritesheets[resID] = surf;
//
//	}
//	else
//	{
//		Game::game->showMsgBox(SDL_GetError());
//	}
//
//}

void ResourceManager::loadTile(std::string f) {

//	loadSprite(f);
}
void ResourceManager::loadFont(std::string f) {

	//loadSprite(f);
}
void ResourceManager::loadBorder(std::string f) {

	//loadSprite(f);
}

SDL_Surface* ResourceManager::getSprite(std::string id) { 
	
	SDL_Surface* ret = spritesheets[id];

	if (ret == nullptr) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Sprite %s not found", id.c_str());
		return spriteDefault;
	}

	return ret;
}
SDL_Surface* ResourceManager::getTile(std::string id) {

	SDL_Surface* ret = spritesheets[id];

	if (ret == nullptr) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Tile %s not found", id.c_str());
		return spriteDefault;
	}

	return ret;
}
SDL_Surface* ResourceManager::getFont(std::string id) {

	SDL_Surface* ret = spritesheets[id];

	if (ret == nullptr) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Font %s not found", id.c_str());
		return spriteDefault;
	}

	return ret;
}
SDL_Surface* ResourceManager::getBorder(std::string id) {

	SDL_Surface* ret = spritesheets[id];

	if (ret == nullptr) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Border %s not found", id.c_str());
		return spriteDefault;
	}

	return ret;
}

std::string ResourceManager::resIdFromPath(std::string path) {

	std::size_t found = path.find("data/");
	std::string sub0 = path.substr(found);
	std::string sub1 = sub0.substr(5, sub0.size());
	std::string sub2 = sub1.substr(0, sub1.size() - 4);
	std::string sub3 = sub2;

	std::replace(sub3.begin(), sub3.end(), '/', '.');
	return sub3;

}

std::string ResourceManager::removeFilenameFromPath(std::string filename, std::string path) {

	return path.substr(0, path.size() - filename.length());

}

void ResourceManager::loadBorders(std::string basePath) {

	const char *dataPath = basePath.append("borders/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		/*if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0) {
		continue;
		}*/

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("border")) {


				const char* borderName = doc.FirstChildElement("border")->FirstChildElement("name")->GetText();
				const char* borderfile = doc.FirstChildElement("border")->FirstChildElement("file")->GetText();

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);


				ResourceManager::manager->loadSprite(resId, filePath.append(borderfile));
			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}

void ResourceManager::loadDungeons(std::string basePath) {

	const char *dataPath = basePath.append("dungeons/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		/*if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0) {
		continue;
		}*/

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("dungeon")) {


				const char* dungeonName = doc.FirstChildElement("dungeon")->FirstChildElement("name")->GetText();
				const char* dungeonFile = doc.FirstChildElement("dungeon")->FirstChildElement("file")->GetText();

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				


				/*DungeonData *newDungeonData = new DungeonData{
					sub2,
					file.name,
					dungeonName
				};

				ResourceManager::manager->dungeonDatas[sub2] = newDungeonData;*/

				ScriptManager::manager->doFile(filePath.append(dungeonFile).c_str());

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}
void ResourceManager::loadEntities(std::string basePath) {

	const char *dataPath = basePath.append("entities/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("entity")) {

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);


				const char* entityName = doc.FirstChildElement("entity")->FirstChildElement("name")->GetText();
				const char* entityType = doc.FirstChildElement("entity")->FirstChildElement("type")->GetText();
				const char* entitySprite = doc.FirstChildElement("entity")->FirstChildElement("sprite")->GetText();
				const char* entityFile = doc.FirstChildElement("entity")->FirstChildElement("file")->GetText();

				EntityData *newEntityData = new EntityData{
					resId,
					file.name,
					entityName,
					new FieldEntityData{ entitySprite }
				};

				ResourceManager::manager->entityDatas[resId] = newEntityData;
				ScriptManager::manager->doFile(filePath.append(entityFile).c_str());

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}
void ResourceManager::loadFonts(std::string basePath) {

	const char *dataPath = basePath.append("fonts/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("font")) {

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				const char* name = doc.FirstChildElement("font")->FirstChildElement("name")->GetText();
				const char* file = doc.FirstChildElement("font")->FirstChildElement("file")->GetText();

				ResourceManager::manager->loadSprite(resId, filePath.append(file));

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}
void ResourceManager::loadHeroes(std::string basePath) {}
void ResourceManager::loadItems(std::string basePath) {}
void ResourceManager::loadMenu(std::string basePath) {

	const char *dataPath = basePath.append("menus/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("menu")) {

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				const char* name = doc.FirstChildElement("menu")->FirstChildElement("name")->GetText();
				const char* file = doc.FirstChildElement("menu")->FirstChildElement("file")->GetText();

				ResourceManager::manager->loadSprite(resId, filePath.append(file));

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}
void ResourceManager::loadScripts(std::string basePath) {}
void ResourceManager::loadSkills(std::string basePath) {}
void ResourceManager::loadSpritesheets(std::string basePath) {

	const char *dataPath = basePath.append("spritesheets/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("spritesheet")) {

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				const char* name = doc.FirstChildElement("spritesheet")->FirstChildElement("name")->GetText();
				const char* file = doc.FirstChildElement("spritesheet")->FirstChildElement("file")->GetText();

				ResourceManager::manager->loadSprite(resId, filePath.append(file));

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}
void ResourceManager::loadTiles(std::string basePath) {

	const char *dataPath = basePath.append("tiles/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("tile")) {

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				const char* name = doc.FirstChildElement("tile")->FirstChildElement("name")->GetText();
				const char* file = doc.FirstChildElement("tile")->FirstChildElement("file")->GetText();

				ResourceManager::manager->loadSprite(resId, filePath.append(file));

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}

void ResourceManager::loadDataFolder() {

	std::string basePath(SDL_GetBasePath());
	basePath.append("data/");
	basePath.append("base/");
	//walk(basePath);

	//borders folder
	loadBorders(basePath);
	loadDungeons(basePath);
	loadEntities(basePath);
	loadFonts(basePath);
	loadHeroes(basePath);
	loadItems(basePath);
	loadMenu(basePath);
	loadScripts(basePath);
	loadSkills(basePath);
	loadSpritesheets(basePath);
	loadTiles(basePath);

}

//void ResourceManager::walk(std::string basePath) {
//
//	const char *dataPath = basePath.c_str();
//	tinydir_dir dir;
//	int i;
//	tinydir_open_sorted(&dir, dataPath);
//
//	for (i = 0; i < dir.n_files; i++)
//	{
//		tinydir_file file;
//		tinydir_readfile_n(&dir, &file, i);
//
//		if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0) {
//			continue;
//		}
//
//		if (file.is_dir)
//		{
//			walk(std::string(basePath).append("/").append(file.name));
//		}
//		else {
//
//			if (strcmp(file.extension, "bmp") == 0) {
//				std::size_t found = basePath.find("data/");
//				std::string sub = basePath.substr(found);
//				//ResourceManager::manager->loadSprite(file.path);
//			}
//
//			if (strcmp(file.extension, "xml") == 0) {
//
//				std::string filePath = std::string(file.path);
//				std::size_t found = filePath.find("data/");
//				std::string sub = filePath.substr(found);
//				std::string sub2 = sub.substr(0, sub.size() - 4);
//
//				std::replace(sub2.begin(), sub2.end(), '/', '.');
//
//				tinyxml2::XMLDocument doc;
//				doc.LoadFile(file.path);
//
//				//entity
//				if (doc.FirstChildElement("entity")) {
//					const char* entityName = doc.FirstChildElement("entity")->FirstChildElement("name")->GetText();
//					const char* entityType = doc.FirstChildElement("entity")->FirstChildElement("type")->GetText();
//					const char* entitySprite = doc.FirstChildElement("entity")->FirstChildElement("sprite")->GetText();
//
//					EntityData *newEntityData = new EntityData{
//						sub2,
//						file.name,
//						entityName,
//						new FieldEntityData{ entitySprite }
//					};
//
//					ResourceManager::manager->entityDatas[sub2] = newEntityData;
//				}
//
//				//dungeon
//				else if (doc.FirstChildElement("dungeon")) {
//
//					const char* dungeonName = doc.FirstChildElement("dungeon")->FirstChildElement("name")->GetText();
//
//					DungeonData *newDungeonData = new DungeonData{
//						sub2,
//						file.name,
//						dungeonName
//					};
//
//					ResourceManager::manager->dungeonDatas[sub2] = newDungeonData;
//				}
//				else {
//				
//					Game::game->showMsgBox("unrecognized xml");
//					Game::game->showMsgBox(file.path);
//				}
//
//			}
//
//			if (strcmp(file.extension, "lua") == 0 && strcmp(file.name, "main.lua") != 0) {
//				std::size_t found = basePath.find("data/");
//				std::string sub = basePath.substr(found);
//
//				ScriptManager::manager->doFile(file.path);
//			}
//		}
//
//	}
//
//	tinydir_close(&dir);
//
//
//}

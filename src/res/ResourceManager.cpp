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
#include "../RenderManager.h"

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

}

void ResourceManager::loadSprite(std::string resId, std::string filePath, bool convertRGBtoIndexed) {

	if (SDL_Surface *surf = SDL_LoadBMP(filePath.c_str())) {

		if (convertRGBtoIndexed) {
			surf = RenderManager::manager->convertRGBtoIndexed(resId, surf);
		}
		spritesheets[resId] = surf;
		SDL_Log("Loaded %s", resId.c_str());

	}
	else
	{
		Game::game->showMsgBox(SDL_GetError());
	}

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
FontData* ResourceManager::getFont(std::string id) {

	FontData* ret = fontDatas[id];

	if (ret == nullptr) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Font %s not found", id.c_str());
		return nullptr;
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

HeroData* ResourceManager::getHeroData(std::string id) {

	return heroDatas[id];
}

EquipData* ResourceManager::getEquipData(std::string id) {

	return equipDatas[id];
}

SkillData* ResourceManager::getSkillData(std::string id) {

	return skillDatas[id];
}

EnemyData* ResourceManager::getEnemyData(std::string id) {

	return enemyDatas[id];
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


				ResourceManager::manager->loadSprite(resId, filePath.append(borderfile), false);
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

				ScriptManager::manager->injectResourceIdGlobal(resId);
				ScriptManager::manager->doFile(filePath.append(dungeonFile).c_str());
				ScriptManager::manager->removeResourceIdGlobal();

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

				FontData *newFontData = new FontData();

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				const char* name = doc.FirstChildElement("font")->FirstChildElement("name")->GetText();
				int height;
				doc.FirstChildElement("font")->FirstChildElement("height")->QueryIntText(&height);

				tinyxml2::XMLElement *charElement = doc.FirstChildElement("font")->FirstChildElement("chars");
				for (tinyxml2::XMLElement* child = charElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
				{
					

					const char* charz = child->FirstChildElement("char")->GetText();
					if (strcmp(charz, "&#032") == 0) {
						charz = " ";
					}

					const char* file = child->FirstChildElement("file")->GetText();
					int width;
					child->FirstChildElement("width")->QueryIntText(&width);

					std::string filePath2 = std::string(filePath).append(file);

					SDL_Surface *surf = SDL_LoadBMP(filePath2.c_str());

					if (surf) {

						SDL_Log("Loaded %s", resId.c_str());
						CharData *newCharData = new CharData();
						newCharData->charz = charz;
						newCharData->fileName = file;
						newCharData->width = width;
						newCharData->surfNormal = RenderManager::manager->convertRGBtoIndexed(resId + " - " + charz, surf);
						newCharData->surfInverted = RenderManager::manager->convertRGBtoIndexed(resId + " - " + charz, RenderManager::manager->invertPixels(resId + " - " + charz, surf));

						newFontData->chars[newCharData->charz] = newCharData;

						SDL_FreeSurface(surf);

					}
					else
					{
						Game::game->showMsgBox(SDL_GetError());
					}
				}

				newFontData->id = resId;
				newFontData->name = name;
				newFontData->height = height;
				newFontData->hSpacing = 1;
				newFontData->vSpacing = 1;

				fontDatas[resId] = newFontData;

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}

void ResourceManager::loadHeroes(std::string basePath) {

	const char *dataPath = basePath.append("heroes/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("hero")) {

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				const char* heroName = doc.FirstChildElement("hero")->FirstChildElement("name")->GetText();

				HeroData *newHeroData = new HeroData{
					resId,
					file.name,
					filePath,
					heroName
				};

				//SKILLS
				tinyxml2::XMLElement *charElement0 = doc.FirstChildElement("hero")->FirstChildElement("skills");
				for (tinyxml2::XMLElement* child = charElement0->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
				{
					const char* skillId = child->/*FirstChildElement("skill")->*/GetText();
					newHeroData->skillsIds.push_back(skillId);

				}

				//STATS
				tinyxml2::XMLElement *charElement = doc.FirstChildElement("hero")->FirstChildElement("stats");
				for (tinyxml2::XMLElement* child = charElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
				{
					Stats newStats = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

					child->QueryIntAttribute("no",		&newStats.levelNo);
					child->QueryIntAttribute("hp",		&newStats.hp);
					child->QueryIntAttribute("mp",		&newStats.mp);
					child->QueryIntAttribute("atk",		&newStats.atk);
					child->QueryIntAttribute("def",		&newStats.def);
					child->QueryIntAttribute("matk",	&newStats.matk);
					child->QueryIntAttribute("mdef",	&newStats.mdef);
					child->QueryIntAttribute("mnd",		&newStats.mnd);
					child->QueryIntAttribute("spd",		&newStats.spd);
					child->QueryIntAttribute("lck",		&newStats.lck);

					newHeroData->stats.push_back(newStats);

				}

				ResourceManager::manager->heroDatas[resId] = newHeroData;

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}

void ResourceManager::loadEquips(std::string basePath) {

	const char *dataPath = basePath.append("equips/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("equip")) {

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				const char* equipName = doc.FirstChildElement("equip")->FirstChildElement("name")->GetText();
				int equipType;
				doc.FirstChildElement("equip")->FirstChildElement("type")->QueryIntText(&equipType);


				EquipData *newEquipData = new EquipData{
					resId,
					file.name,
					filePath,
					equipName,
					(EquipType) equipType
				};

				tinyxml2::XMLElement *charElement = doc.FirstChildElement("equip")->FirstChildElement("skills");
				for (tinyxml2::XMLElement* child = charElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
				{
					const char* skillId = child->/*FirstChildElement("skill")->*/GetText();
					newEquipData->skillsIds.push_back(skillId);

				}

				ResourceManager::manager->equipDatas[resId] = newEquipData;

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}

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

				ResourceManager::manager->loadSprite(resId, filePath.append(file), true);

			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}
void ResourceManager::loadScripts(std::string basePath) {}

void ResourceManager::loadSkills(std::string basePath) {

	const char *dataPath = basePath.append("skills/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("skill")) {

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				const char* skillName = doc.FirstChildElement("skill")->FirstChildElement("name")->GetText();
				const char* skillScript = doc.FirstChildElement("skill")->FirstChildElement("script")->GetText();

				SkillData *newSkillData = new SkillData{
					resId,
					file.name,
					filePath,
					skillName,
					skillScript
				};

				ResourceManager::manager->skillDatas[resId] = newSkillData;
				ScriptManager::manager->doFile(filePath.append(skillScript).c_str());


			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}

void ResourceManager::loadEnemies(std::string basePath) {

	const char *dataPath = basePath.append("enemies/").c_str();
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++) {

		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.extension, "xml") == 0) {

			tinyxml2::XMLDocument doc;
			doc.LoadFile(file.path);

			if (doc.FirstChildElement("enemy")) {

				std::string resId = resIdFromPath(file.path);
				std::string filePath = removeFilenameFromPath(file.name, file.path);

				const char* enemyName = doc.FirstChildElement("enemy")->FirstChildElement("name")->GetText();
				const char* enemyScript = doc.FirstChildElement("enemy")->FirstChildElement("script")->GetText();

				int hp;
				doc.FirstChildElement("enemy")->FirstChildElement("hp")->QueryIntText(&hp);

				int strength;
				doc.FirstChildElement("enemy")->FirstChildElement("strength")->QueryIntText(&strength);
				
				int speed;
				doc.FirstChildElement("enemy")->FirstChildElement("speed")->QueryIntText(&speed);

				int vitality;
				doc.FirstChildElement("enemy")->FirstChildElement("vitality")->QueryIntText(&vitality);

				int intelligence;
				doc.FirstChildElement("enemy")->FirstChildElement("intelligence")->QueryIntText(&intelligence);

				int mind;
				doc.FirstChildElement("enemy")->FirstChildElement("mind")->QueryIntText(&mind);


				EnemyData *newEnemyData = new EnemyData{
					resId,
					file.name,
					filePath,
					enemyName,
					enemyScript,
					hp,
					strength,
					speed,
					vitality,
					intelligence,
					mind

				};

				ResourceManager::manager->enemyDatas[resId] = newEnemyData;
				ScriptManager::manager->doFile(filePath.append(enemyScript).c_str());


			}
			else {
				Game::game->showMsgBox("unrecognized xml");
				Game::game->showMsgBox(file.path);

			}
		}
	}

}

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

				ResourceManager::manager->loadSprite(resId, filePath.append(file), true);

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

				ResourceManager::manager->loadSprite(resId, filePath.append(file), true);

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
	loadEquips(basePath);
	loadItems(basePath);
	loadMenu(basePath);
	loadScripts(basePath);
	loadSkills(basePath);
	loadEnemies(basePath);
	loadSpritesheets(basePath);
	loadTiles(basePath);

}

int Resource_getEntitySpriteId(lua_State *L) {

	std::string entityID = lua_tostring(L, 1);
	
	std::string spriteID = ResourceManager::manager->entityDatas[entityID]->data->spritesheet;

	lua_pushstring(L, spriteID.c_str());

	return 1;
}

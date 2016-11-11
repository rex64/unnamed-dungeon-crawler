#ifdef __APPLE__

    #include <SDL2/SDL.h>

    extern "C" {
        #include <lua.h>
        #include <lualib.h>
        #include <lauxlib.h>
    }

#elif _WIN32

    #define SDL_MAIN_HANDLED
    #include <SDL.h>
    #include <stdio.h>
    #include <lua.hpp>

#endif

#include <iostream>
#include "Game.h"
#include <tinydir.h>
#include "res/ResourceManager.h"
#include "ScriptManager.h"
#include <algorithm>
#include "tinyxml2.h"

/*
const static char *Obj_typename = "ObjTypename";

void check_Obj(lua_State *L, int i) {
	luaL_checkudata(L, i, Obj_typename);
}

int MyLib_MakeObj(lua_State *L) {
	printf("In MyLib_MakeObj\n");
	lua_newuserdata(L, sizeof(int*));
	luaL_setmetatable(L, Obj_typename);
	return 1;
}
int Obj__gc(lua_State *L) {
	printf("In Obj__gc\n");
	return 0;
}
int Obj_method(lua_State *L) {
	printf("In Obj_method\n");
	check_Obj(L, 1);
	return 0;
}

int luaopen_MyLib(lua_State *L) {
	static const luaL_Reg Obj_lib[] = {
		{ "method", &Obj_method },
		{ NULL, NULL }
	};

	static const luaL_Reg MyLib_lib[] = {
		{ "MakeObj", &MyLib_MakeObj },
		{ NULL, NULL }
	};

	luaL_newlib(L, MyLib_lib);

	// Stack: MyLib
	luaL_newmetatable(L, Obj_typename); // Stack: MyLib meta
	luaL_newlib(L, Obj_lib);
	lua_setfield(L, -2, "__index"); // Stack: MyLib meta

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, Obj__gc); // Stack: MyLib meta "__gc" fptr
	lua_settable(L, -3); // Stack: MyLib meta
	lua_pop(L, 1); // Stack: MyLib

	return 1;
}
*/

void walk(std::string basePath) {

	

	const char *dataPath = basePath.c_str();
	printf("Entering: %s", dataPath);
	printf("\n");
	tinydir_dir dir;
	int i;
	tinydir_open_sorted(&dir, dataPath);

	for (i = 0; i < dir.n_files; i++)
	{
		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0) {
			continue;
		}

		if (file.is_dir)
		{
			//printf("/");
			walk(std::string(basePath).append("/").append(file.name));
		}
		else {
			printf("%s", file.name);
			printf("\n");

			if (strcmp(file.extension, "bmp") == 0){
				std::size_t found = basePath.find("data/");
				std::string sub = basePath.substr(found);
				//printf("%s", found);
				ResourceManager::manager->loadSprite(file.path);
			}

			if (strcmp(file.extension, "xml") == 0) {
				
				std::string filePath = std::string(file.path);
				std::size_t found = filePath.find("data/");
				std::string sub = filePath.substr(found);
				std::string sub2 = sub.substr(0, sub.size() - 4);

				std::replace(sub2.begin(), sub2.end(), '/', '.');

				tinyxml2::XMLDocument doc;
				doc.LoadFile(file.path);
				const char* entityName = doc.FirstChildElement("entity")->FirstChildElement("name")->GetText();
				const char* entityType = doc.FirstChildElement("entity")->FirstChildElement("type")->GetText();

				EntityData *newEntityData = new EntityData{ sub2, file.name, entityName, new FieldEntityData{ "data.base.spritesheets.stairs" } };
				ResourceManager::manager->entityDatas[sub2] = newEntityData;

				
			}

			if (strcmp(file.extension, "lua") == 0 && strcmp(file.name, "main.lua") != 0) {
				std::size_t found = basePath.find("data/");
				std::string sub = basePath.substr(found);

				ScriptManager::manager->doFile(file.path);
			}
		}
		
	}

	tinydir_close(&dir);


}

int main(int argc, char* argv[]) {

	

	Game *g = new Game();
	g->init();
	/*
	int iarg;
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	luaL_requiref(L, "MyLib", luaopen_MyLib, 1);

	if (luaL_dofile(L, "data/base/scripts/test.lua")) {
		std::cout << lua_tostring(L, -1);
	}

	lua_close(L);
	std::cout << "CIAO\n";


	*/
	
	std::string basePath(SDL_GetBasePath());
	basePath.append("data");
	//basePath.append("base\\");
	walk(basePath);
	

	g->run();

    return 0;

}

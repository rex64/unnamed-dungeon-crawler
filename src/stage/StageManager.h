#pragma once
#include "Stage.h"

#ifdef __APPLE__
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#elif _WIN32
#include <lua.hpp>
#endif

class StageManager
{
public:
	StageManager();
	~StageManager();

	void init();
	static StageManager *manager;
	Stage *currStage;

	void onInputUp();
	void onInputRight();
	void onInputDown();
	void onInputLeft();

private:
	
};

extern "C" {


	int Stage_onInputUp(lua_State *L);
	int Stage_onInputRight(lua_State *L);
	int Stage_onInputDown(lua_State *L);
	int Stage_onInputLeft(lua_State *L);

}
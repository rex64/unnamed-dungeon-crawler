#include <stdio.h>

#ifdef __APPLE__
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#elif _WIN32
#include <lua.hpp>
#endif

extern "C" {
	
	/*int Save_getCurrentPartySize(lua_State *L);
	int Save_getPartyMemberName(lua_State *L);
	int Save_getHeroSkills(lua_State *L);
	int Save_getSkillName(lua_State *L);*/

	int Data_getEnemyData(lua_State *L);
	
}

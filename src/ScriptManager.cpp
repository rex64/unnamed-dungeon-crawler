#include "ScriptManager.h"
#include "Game.h"

ScriptManager* ScriptManager::manager;

ScriptManager::ScriptManager()
{
}


ScriptManager::~ScriptManager()
{
}

void ScriptManager::init() {

	manager = this;

	//Lua
	m_L = luaL_newstate();
	luaL_openlibs(m_L);

	lua_register(m_L, "luaTestFunc", luaTestFunc);

	luaL_dostring(m_L, "io.write(\"luaTestFunc\")");
	luaL_dostring(m_L, "luaTestFunc(\"First\", \"Second\", 112233)");

	luaL_dostring(m_L, "io.write(\"ciao\")");

	/*
	lua_newtable(state);
	lua_setglobal(state, "game");

	lua_getglobal(state, "game");
	lua_pushstring(state, "system");
	lua_newtable(state);
	lua_settable(state, -3);
	lua_pop(state, -1);
	*/

	lua_newtable(m_L);
	lua_setglobal(m_L, "system");

	lua_getglobal(m_L, "system");
	lua_pushstring(m_L, "quit");
	lua_pushcfunction(m_L, luaQuitGame);
	lua_settable(m_L, -3);
	lua_pop(m_L, -1);

	//    luaL_dostring(m_L, "system.quit();");


	//    stackDump(m_L);

	if (luaL_dofile(m_L, "data/base/scripts/main.lua")) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		//SDL_ShowSimpleMessageBox(0, "ERRORL", lua_tostring(m_L, -1), window);
		// printf("Couldn't load file: %s\n", lua_tostring(m_L, -1));
		lua_pop(m_L, -1);

		stackDump(m_L);

		//exit(1);
	}


}

void ScriptManager::doString(const char *str)
{
	if (luaL_dostring(m_L, str)) {
		Game::game->showMsgBox(lua_tostring(m_L, -1));
		lua_pop(m_L, -1);

		stackDump(m_L);
	}
}


	static void stackDump(lua_State *L) {

		printf("LUA STACK DUMP--------\n");

		int i;
		int top = lua_gettop(L);
		for (i = 1; i <= top; i++) {  /* repeat for each level */
			int t = lua_type(L, i);
			switch (t) {

			case LUA_TSTRING:  /* strings */
				printf("`%s'", lua_tostring(L, i));
				break;

			case LUA_TBOOLEAN:  /* booleans */
				printf(lua_toboolean(L, i) ? "true" : "false");
				break;

			case LUA_TNUMBER:  /* numbers */
				printf("%g", lua_tonumber(L, i));
				break;

			default:  /* other values */
				printf("%s", lua_typename(L, t));
				break;

			}
			printf("  ");  /* put a separator */
		}
		printf("\n");  /* end the listing */
	}

	//http://www.lua.org/manual/5.3/manual.html#lua_CFunction
	static int luaTestFunc(lua_State* state)
	{
		/* number of arguments */
		int args = lua_gettop(state);

		for (int n = 1; n <= args; ++n) {
			printf("  arg %d: '%s'\n", n, lua_tostring(state, n));
		}

		lua_pushnumber(state, 123);
		return 1; /* number of results */
	}

	static int luaQuitGame(lua_State* state) {

		//    printf("luaQuitGame..\n");

		//quit = true;

		Game::game->quit();

		return 0;
	}
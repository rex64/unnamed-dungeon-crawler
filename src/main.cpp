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

#include "Game.h"


int main(int argc, char* argv[]) {

	Game *g = new Game();
	g->init();

	g->run();

    return 0;

}

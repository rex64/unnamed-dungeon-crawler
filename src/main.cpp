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

#include <string>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 225

#define GAME_WIDTH 256
#define GAME_HEIGHT 144

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

void renderText(std::string str, SDL_Surface* charSet, SDL_Surface* surf) {

	unsigned int i = 0;
	for (char& c : str) {
		//printf("%c", c);
		unsigned int charIndex = c - 32;
		SDL_Rect src = { 8 * charIndex, 0, 8, 8 };
		SDL_Rect dst = { 8 * i, 16, 8, 8 };

		SDL_BlitSurface(charSet, &src, surf, &dst);
		++i;
	}

}

int main(int argc, char* argv[]) {

    SDL_version compiled;
    SDL_version linked;
    
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    
    printf("We compiled against SDL version %d.%d.%d ...\n",
           compiled.major, compiled.minor, compiled.patch);
    printf("We are linking against SDL version %d.%d.%d.\n",
           linked.major, linked.minor, linked.patch);
    
    
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
       "unamed-dungeon-crawler",
       SDL_WINDOWPOS_UNDEFINED,
       SDL_WINDOWPOS_UNDEFINED,
       SCREEN_WIDTH*2,
       SCREEN_HEIGHT*2,
	   SDL_WINDOW_RESIZABLE
    );    
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    
    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                                SDL_PIXELFORMAT_ARGB8888,
                                                SDL_TEXTUREACCESS_STREAMING,
                                                SCREEN_WIDTH, SCREEN_HEIGHT);
    
//    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
//    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH*4, SCREEN_HEIGHT*4);
    
    //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", SDL_GetError(), window);
    
    SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_Surface *game   = SDL_CreateRGBSurface(0, GAME_WIDTH, GAME_HEIGHT, 32, 0, 0, 0, 0);

    SDL_Surface *testSurface = SDL_LoadBMP("data/base/test.bmp");
    SDL_Surface *borderSurface = SDL_LoadBMP("data/base/borders/border.bmp");
	SDL_Surface *tile00Surface = SDL_LoadBMP("data/base/tiles/tile00.bmp");
	SDL_Surface *tile01Surface = SDL_LoadBMP("data/base/tiles/tile01.bmp");
	SDL_Surface *player = SDL_LoadBMP("data/base/spritesheets/player.bmp");
	SDL_Surface *bmpFont = SDL_LoadBMP("data/base/fonts/standard_font.bmp");

    bool quit = false;

    SDL_Event e;

	//SDL_Rect pos = { 0,40,100,100 };

	//Lua
	lua_State *state = luaL_newstate();
	luaL_openlibs(state);

	lua_register(state, "luaTestFunc", luaTestFunc);

	luaL_dostring(state, "io.write(\"luaTestFunc\")");
	luaL_dostring(state, "luaTestFunc(\"First\", \"Second\", 112233)");
	

	//Dungeon
	int tilesArray[] = { 
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	int arrayWidth  = 16;
	int arrayHeight = 9;

	int playerPos = 0;
	 
    while (!quit)
    {

        while (SDL_PollEvent(&e) != 0)
        {
            
            const Uint8 *state = SDL_GetKeyboardState(NULL);

            
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (state[SDL_SCANCODE_LEFT]) {
                
				//int oldPos = playerPos;

				int x = playerPos % arrayWidth;
				int y = (playerPos / arrayWidth) % arrayHeight;

				x -= 1;

				playerPos = x + arrayWidth*y;
            } else
            
            if (state[SDL_SCANCODE_RIGHT]) {
               
				int x = playerPos % arrayWidth;
				int y = (playerPos / arrayWidth) % arrayHeight;

				x += 1;

				playerPos = x + arrayWidth*y;
            } else

			if (state[SDL_SCANCODE_UP]) {

				int x = playerPos % arrayWidth;
				int y = (playerPos / arrayWidth) % arrayHeight;

				y -= 1;

				playerPos = x + arrayWidth*y;
			} else

			if (state[SDL_SCANCODE_DOWN]) {

				int x = playerPos % arrayWidth;
				int y = (playerPos / arrayWidth) % arrayHeight;

				y += 1;

				playerPos = x + arrayWidth*y;
			}
            
        }

		//clear screen surface
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 0));
		SDL_FillRect(game, NULL, SDL_MapRGB(screen->format, 0, 255, 0));

		//render tiles
		for (size_t i = 0; i < arrayWidth * arrayHeight; i++)
		{
			int x = i % arrayWidth;
			int y = (i / arrayWidth) % arrayHeight;

			SDL_Rect pos = { x * 16, y * 16, 16, 16 };

			//printf("x: %i , y: %i\n", x, y);

			if (tilesArray[i] == 0) {

				SDL_BlitSurface(tile00Surface, NULL, game, &pos);
			} else 

			if (tilesArray[i] == 1) {

				SDL_BlitSurface(tile01Surface, NULL, game, &pos);
			}
		}

		//render player

		{

			int x = playerPos % arrayWidth;
			int y = (playerPos / arrayWidth) % arrayHeight;

			SDL_Rect pos = { x * 16, y * 16, 16, 16 };
			SDL_BlitSurface(player, NULL, game, &pos);
		}


		//SDL_BlitSurface(testSurface, 0, game, NULL);

		SDL_BlitSurface(borderSurface, 0, screen, 0);

		SDL_Rect location = { 72,40,100,100 };
		SDL_BlitSurface(game, 0, screen, &location);

		//test
		SDL_BlitSurface(bmpFont, 0, screen, 0);
		renderText(" 0123!", bmpFont, screen);


        SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, 0, 0);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(16);
    }

	lua_close(state);

    SDL_FreeSurface(testSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#endif

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 225

#define GAME_WIDTH 256
#define GAME_HEIGHT 144

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
       0
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

    SDL_Surface *testSurface = SDL_LoadBMP("test.bmp");
    SDL_Surface *borderSurface = SDL_LoadBMP("border.bmp");

    bool quit = false;

    SDL_Event e;

	//SDL_Rect pos = { 0,40,100,100 };

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
                //DestR.x -= 1;
            }
            
            if (state[SDL_SCANCODE_RIGHT]) {
                //DestR.x += 1;
            }
            
        }

		//clear screen surface
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 0));
		SDL_FillRect(game, NULL, SDL_MapRGB(screen->format, 0, 255, 0));

		SDL_BlitSurface(testSurface, 0, game, NULL);

		SDL_BlitSurface(borderSurface, 0, screen, 0);

		SDL_Rect location = { 72,40,100,100 };
		SDL_BlitSurface(game, 0, screen, &location);
        
        SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, 0, 0);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(16);
    }

    SDL_FreeSurface(testSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif _WIN32
#define SDL_MAIN_HANDLED
#include <SDL.h>
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("unamed-dungeon-crawler", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface   *windowSurface = SDL_GetWindowSurface(window);
    SDL_Surface *testSurface = SDL_LoadBMP("test.bmp");

    bool quit = false;

    SDL_Event e;

    while (!quit)
    {

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            SDL_BlitSurface(testSurface, NULL, windowSurface, NULL);

            SDL_UpdateWindowSurface(window);
        }

    }

    SDL_FreeSurface(testSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

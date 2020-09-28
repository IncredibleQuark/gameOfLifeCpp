//
// Created by lukasz on 28/9/20.
//

#include "Display.h"
#include "GridDrawer.h"
#include "Pattern.h"
#include "PatternLoader.h"
#include "Simulation.h"

#include <SDL2/SDL.h>

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <utility>


#if defined(_WIN32) && defined(_DEBUG)
#include <crtdbg.h>
#endif

using namespace std;


extern "C" int main(int argc, char *argv[]) {
#if defined(_WIN32) && defined(_DEBUG)
    _CrtSetDdbFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    std::srand((unsigned int) std::time(NULL));
    gameOfLife::Simulation simulation(320, 240, 4, 4);
    simulation.Randomize();

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window *window = SDL_CreateWindow(
            "Game Of Life",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            simulation.Display().Width(),
            simulation.Display().Height(),
            SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STATIC,
            simulation.Display().Width(),
            simulation.Display().Height());

    SDL_bool quit = SDL_FALSE;
    SDL_Event event = {0};
    int fps = 30;

    bool paused = true;
    int step = 0;

    while (!quit) {
        Uint32 start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = SDL_TRUE;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE)
                        paused = !paused;
                    else if (event.key.keysym.sym == SDLK_ESCAPE)
                        quit = SDL_TRUE;
                    break;

                default:
                    break;
            }
        }

        if (!paused)
            simulation.Step();

        SDL_UpdateTexture(texture, nullptr, simulation.Display().Pixels(),
                          simulation.Display().Width() * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        Uint32 end = SDL_GetTicks();

        int delay = 1000 / fps - (end - start);

        if (delay > 0)
            SDL_Delay(delay);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

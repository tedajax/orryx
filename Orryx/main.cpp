#include <iostream>

#include "OrryxMath.h"

#include <SDL2/SDL.h>

using namespace orx;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Orryx",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Delay(2000);
    
    SDL_Quit();

    return 0;
}
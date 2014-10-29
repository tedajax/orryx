#include <iostream>

#include "OrryxMath.h"
#include "Window.h"

#include <SDL2/SDL.h>

using namespace orx;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    WindowConfig config;
    config.m_title = "Orryx";
    config.m_position.m_x = SDL_WINDOWPOS_UNDEFINED;
    config.m_position.m_y = SDL_WINDOWPOS_UNDEFINED;
    config.m_dimensions.m_x = 800;
    config.m_dimensions.m_y = 600;
    config.m_flags = SDL_WINDOW_SHOWN;
    
    Window window(config);
    window.create();

    SDL_Delay(2000);

    window.terminate();
    
    SDL_Quit();

    return 0;
}
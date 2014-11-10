#include <iostream>

#include "OrryxMath.h"
#include "Window.h"
#include "Application.h"
#include "ConfigData.h"

#include <SDL2/SDL.h>

using namespace orx;

int main(int argc, char* argv[])
{
    int screenWidth = 1280;
    int screenHeight = 720;

    WindowConfig windowConfig;
    windowConfig.m_title = "Orryx";
    windowConfig.m_position.m_x = SDL_WINDOWPOS_UNDEFINED;
    windowConfig.m_position.m_y = SDL_WINDOWPOS_UNDEFINED;
    windowConfig.m_dimensions.m_x = screenWidth;
    windowConfig.m_dimensions.m_y = screenHeight;
    windowConfig.m_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    ConfigData::set("screen_width", screenWidth);
    ConfigData::set("screen_height", screenHeight);
    
    Application application({ "Orryx", windowConfig });
    bool result = application.initialize();

    if (!result)
    {
        std::cout << "Application failed to initialize!\n";
        std::cin.get();
        return -1;
    }

    return application.run(argc, argv);
}
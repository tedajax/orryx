#ifndef ORRYX_APPLICATION_H
#define ORRYX_APPLICATION_H

#include "OrryxTypes.h"
#include "OrryxTime.h"
#include "Window.h"
#include "Input.h"

#include <SDL2/SDL.h>

namespace orx
{
    struct ApplicationConfig
    {
        char* m_appName;
        WindowConfig m_windowConfig;
    };

    class Application
    {
    public:
        Application(ApplicationConfig config);
        ~Application();

        bool initialize();
        int run(int argc, char* argv[]);

    private:
        Window m_window;
        SDL_GLContext m_context;
        bool m_isRunning;
        bool m_isInitialized;
        char* m_appName;

        Time m_time;
        Input m_input;

        void handleEvent(SDL_Event event);
        void handleKeyDown(SDL_KeyboardEvent event);
        void handleKeyUp(SDL_KeyboardEvent event);
        void handleResize(int w, int h);
        void update();
        void render();
    };
}

#endif
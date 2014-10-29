#ifndef ORRYX_WINDOWS_H
#define ORRYX_WINDOWS_H

#include <SDL2/SDL.h>
#include "OrryxTypes.h"

namespace orx
{
    struct WindowCoord
    {
        WindowCoord()
            : m_x(0), m_y(0)
        { }

        WindowCoord(i32 x, i32 y)
            : m_x(x), m_y(y)
        { }

        i32 m_x;
        i32 m_y;
    };

    struct WindowConfig
    {
        char* m_title;
        WindowCoord m_position;
        WindowCoord m_dimensions;
        u32 m_flags;
    };

    class Window
    {
    public:
        Window(WindowConfig config);
        ~Window();

        void create();
        void terminate();

        SDL_Window* raw() { return m_window; }

    private:
        WindowConfig m_config;
        SDL_Window* m_window;
    };
}

#endif
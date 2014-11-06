#ifndef ORRYX_INPUT_H
#define ORRYX_INPUT_H

#include <SDL2/SDL.h>

namespace orx
{
    class Input
    {
    public:
        Input();
        ~Input();

        bool getKey(SDL_Scancode key);
        bool getKeyDown(SDL_Scancode key);
        bool getKeyUp(SDL_Scancode key);

        void update();

        void onKeyEvent(const SDL_KeyboardEvent& event);

    private:
        bool m_previousState[SDL_NUM_SCANCODES];
        bool m_currentState[SDL_NUM_SCANCODES];
    };
}

#endif
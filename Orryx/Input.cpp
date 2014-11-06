#include "Input.h"

namespace orx
{
    Input::Input()
    {
        for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_previousState[i] = false;
            m_currentState[i] = false;
        }
    }

    Input::~Input()
    {

    }

    bool Input::getKey(SDL_Scancode key)
    {
        return m_currentState[key];
    }

    bool Input::getKeyDown(SDL_Scancode key)
    {
        return m_currentState[key] && !m_previousState[key];
    }

    bool Input::getKeyUp(SDL_Scancode key)
    {
        return !m_currentState[key] && m_previousState[key];
    }

    void Input::update()
    {
        for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_previousState[i] = m_currentState[i];
        }
    }

    void Input::onKeyEvent(const SDL_KeyboardEvent& event)
    {
        SDL_Scancode code = event.keysym.scancode;
        bool down = (event.state == SDL_PRESSED);
        m_currentState[code] = down;
    }
}
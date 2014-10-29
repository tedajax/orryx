#include "Window.h"

#include <cassert>

namespace orx
{
    Window::Window(WindowConfig config)
    {
        m_config = config;
        m_window = nullptr;
    }

    Window::~Window()
    {
        if (m_window)
        {
            SDL_DestroyWindow(m_window);
        }
    }

    void Window::create()
    {
        assert(m_window == nullptr);

        m_window = SDL_CreateWindow(m_config.m_title,
                                    m_config.m_position.m_x,
                                    m_config.m_position.m_y,
                                    m_config.m_dimensions.m_x,
                                    m_config.m_dimensions.m_y,
                                    m_config.m_flags);
    }

    void Window::terminate()
    {
        assert(m_window != nullptr);

        SDL_DestroyWindow(m_window);
    }
}
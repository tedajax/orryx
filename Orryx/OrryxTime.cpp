#include "OrryxTime.h"

#include <SDL2/SDL.h>

namespace orx
{
    void Time::update()
    {
        u64 nanosecondCount = 0;
        
        {
            u64 performanceCounter = SDL_GetPerformanceCounter();
            u64 frequency = SDL_GetPerformanceFrequency();

            u64 diff = performanceCounter - m_lastFrameTicks;
            diff *= 1000000000;
            diff /= frequency;

            nanosecondCount = diff;

            m_lastFrameTicks = performanceCounter;
        }

        m_lastFrameTime = m_nanosecondsSinceStart;
        m_nanosecondsSinceStart += nanosecondCount;

        m_secondsTimer += nanosecondCount;
        if (m_secondsTimer >= 1000000000)
        {
            m_secondsTimer = 0;
            m_fps = m_framesThisSecond;
            m_framesThisSecond = 0;
            m_elapsedSecond = true;
        }
        else
        {
            ++m_framesThisSecond;
        }        
    }

    f32 Time::delta()
    {
        return ((f32)m_nanosecondsSinceStart - (f32)m_lastFrameTime) / 1000000000;
    }
}
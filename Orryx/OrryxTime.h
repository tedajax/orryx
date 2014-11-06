#ifndef ORRYX_TIME_H
#define ORRYX_TIME_H

#include "OrryxTypes.h"

namespace orx
{
    class Time
    {
    public:
        Time()
            : m_nanosecondsSinceStart(0),
            m_lastFrameTicks(0),
            m_lastFrameTime(0),
            m_secondsTimer(0),
            m_framesThisSecond(0),
            m_fps(0),
            m_elapsedSecond(false)
        { }

        ~Time() { }

        void update();
        f32 delta();
        u32 fps() { return m_fps; }
        bool secondElapsed()
        {
            if (m_elapsedSecond)
            {
                m_elapsedSecond = false;
                return true;
            }
            return false;
        }

    private:
        // All times in nanoseconds
        u64 m_nanosecondsSinceStart;
        u64 m_lastFrameTicks;
        u64 m_lastFrameTime;
        u64 m_secondsTimer;
        u32 m_framesThisSecond;

        u32 m_fps;

        bool m_elapsedSecond;
    };
}

#endif
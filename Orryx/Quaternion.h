#ifndef ORRYX_QUATERNION_H
#define ORRYX_QUATERNION_H

#include "OrryxMath.h"
#include "OrryxTypes.h"

namespace orx
{
    class Quaternion
    {
    public:
        Quaternion();
        Quaternion(const Quaternion& other);

        f32 getX() const { return m_data[0]; }
        f32 getY() const { return m_data[1]; }
        f32 getZ() const { return m_data[2]; }
        f32 getW() const { return m_data[3]; }

        f32 setX(f32 x) { return m_data[0] = x; }
        f32 setY(f32 y) { return m_data[1] = y; }
        f32 setZ(f32 z) { return m_data[2] = z; }
        f32 setW(f32 w) { return m_data[3] = w; }

    private:
        f32 m_data[4];
    };
}

#endif
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
        Quaternion(f32 x, f32 y, f32 z, f32 w);
        Quaternion(Vector3 vector, f32 scalar);

        Quaternion& normalize();
        Quaternion& conjugate();
        f32 length();
        f32 lengthSqr();

        static Quaternion normalize(const Quaternion& quaternion);
        static Quaternion conjugate(const Quaternion& quaternion);
        static Quaternion inverse(const Quaternion& quaternion);
        static Quaternion axisAngle(const Vector3& vector, f32 axis);

        f32 getX() const { return m_data[0]; }
        f32 getY() const { return m_data[1]; }
        f32 getZ() const { return m_data[2]; }
        f32 getW() const { return m_data[3]; }

        f32 setX(f32 x) { return m_data[0] = x; }
        f32 setY(f32 y) { return m_data[1] = y; }
        f32 setZ(f32 z) { return m_data[2] = z; }
        f32 setW(f32 w) { return m_data[3] = w; }

        void set(f32 x = 0.f, f32 y = 0.f, f32 z = 0.f, f32 w = 0.f)
        {
            setX(x);
            setY(y);
            setZ(z);
            setW(w);
        }

        static Quaternion identity() { return Quaternion(0.f, 0.f, 0.f, 1.f); }
        static const Quaternion IDENTITY;

    private:
        f32 m_data[4];
    };
}

#endif
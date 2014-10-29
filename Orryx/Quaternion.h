#ifndef ORRYX_QUATERNION_H
#define ORRYX_QUATERNION_H

#include "OrryxMath.h"
#include "OrryxTypes.h"

namespace orx
{
    class Matrix;
    class Vector3;

    class Quaternion
    {
    public:
        Quaternion();
        Quaternion(const Quaternion& other);
        Quaternion(f32 x, f32 y, f32 z, f32 w);
        Quaternion(Vector3 vector, f32 scalar);

        Quaternion& operator=(const Quaternion& rhs);
        Quaternion& operator+=(const Quaternion& rhs);
        Quaternion& operator-=(const Quaternion& rhs);
        Quaternion& operator*=(const Quaternion& rhs);
        Quaternion& operator*=(const f32 rhs);
        Quaternion& operator/=(const Quaternion& rhs);

        bool operator==(const Quaternion& rhs);
        bool operator!=(const Quaternion& rhs);

        Quaternion& normalize();
        Quaternion& conjugate();
        f32 length() const;
        f32 lengthSqr() const;

        static Quaternion normalize(const Quaternion& quaternion);
        static Quaternion conjugate(const Quaternion& quaternion);
        static Quaternion inverse(const Quaternion& quaternion);
        static Quaternion fromAxisAngle(const Vector3& axis, f32 angle);
        static Quaternion fromYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll);
        static Quaternion fromRotationMatrix(const Matrix& matrix);
        static Quaternion fromLookAt(const Vector3& source, const Vector3 target);
        static f32 dot(const Quaternion& q1, const Quaternion& q2);
        static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, f32 t);
        static Quaternion lerp(const Quaternion& q1, const Quaternion& q2, f32 t);
        static Quaternion negate(const Quaternion& quaternion);

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
            setX(x); setY(y); setZ(z); setW(w);
        }

        static Quaternion identity() { return Quaternion(0.f, 0.f, 0.f, 1.f); }
        static const Quaternion IDENTITY;

    private:
        f32 m_data[4];
    };

    inline Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs)
    {
        return Quaternion(lhs.getX() + rhs.getX(),
                          lhs.getY() + rhs.getY(),
                          lhs.getZ() + rhs.getZ(),
                          lhs.getW() + rhs.getW());
    }

    inline Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs)
    {
        return Quaternion(lhs.getX() - rhs.getX(),
                          lhs.getY() - rhs.getY(),
                          lhs.getZ() - rhs.getZ(),
                          lhs.getW() - rhs.getW());
    }

    inline Quaternion operator-(const Quaternion& quaternion)
    {
        return Quaternion::negate(quaternion);
    }

    inline Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
    {
        Quaternion quaternion;
        f32 x1 = lhs.getX();
        f32 y1 = lhs.getY();
        f32 z1 = lhs.getZ();
        f32 w1 = lhs.getW();

        f32 x2 = rhs.getX();
        f32 y2 = rhs.getY();
        f32 z2 = rhs.getZ();
        f32 w2 = rhs.getW();

        f32 yzDiff = (y1 * z2) - (z1 * y2);
        f32 xzDiff = (z1 * x2) - (x1 * z2);
        f32 xyDiff = (x1 * y2) - (y1 * x2);
        f32 prodSum = (x1 * x2) + (y1 * y2) + (z1 * z2);

        quaternion.setX((x1 * w2) + (x2 * w1) + yzDiff);
        quaternion.setY((y1 * w2) + (y2 * w1) + xzDiff);
        quaternion.setZ((z1 * w2) + (z2 * w1) + xyDiff);
        quaternion.setW(w1 * w2 - prodSum);
        return quaternion;
    }

    inline Quaternion operator*(const Quaternion& lhs, const f32 rhs)
    {
        return Quaternion(lhs.getX() * rhs,
                          lhs.getY() * rhs,
                          lhs.getZ() * rhs,
                          lhs.getW() * rhs);
    }

    inline Quaternion operator/(const Quaternion& lhs, const Quaternion& rhs)
    {
        return Quaternion(lhs.getX() / rhs.getX(),
                          lhs.getY() / rhs.getY(),
                          lhs.getZ() / rhs.getZ(),
                          lhs.getW() / rhs.getW());
    }
}

#endif
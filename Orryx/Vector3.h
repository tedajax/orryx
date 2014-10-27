#ifndef ORRYX_VECTOR3_H
#define ORRYX_VECTOR3_H

#include "OrryxTypes.h"
#include "OrryxMath.h"

namespace orx
{
    class Vector2;

    class Vector3
    {
    public:
        Vector3();
        Vector3(f32 x, f32 y, f32 z);
        Vector3(const Vector3& other);
        Vector3(const Vector2& vec, f32 z = 0.f);

        Vector3& operator=(const Vector3& rhs);
        Vector3& operator+=(const Vector3& rhs);
        Vector3& operator-=(const Vector3& rhs);
        Vector3& operator*=(const f32& rhs);
        Vector3& operator/=(const f32& rhs);

        f32 operator[](const int i) const { return m_data[i]; }

        bool operator==(const Vector3& rhs) const;
        bool operator!=(const Vector3& rhs) const;

        Vector3& normalize();
        Vector3& negate();
        Vector3& clamp(const Vector3& min, const Vector3& max);
        f32 length() const;
        f32 lengthSqr() const;
        f32 dot(const Vector3& vec) const;
        Vector3 cross(const Vector3& vec) const;

        static Vector3 normalize(const Vector3& vec);
        static Vector3 negate(const Vector3& vec);
        static Vector3 clamp(const Vector3& vec, const Vector3& min, const Vector3& max);
        static Vector3 lerp(const Vector3& start, const Vector3& end, const f32& t);
        static f32 length(const Vector3& vec);
        static f32 lengthSqr(const Vector3& vec);
        static f32 dot(const Vector3& v1, const Vector3& v2);
        static Vector3& cross(const Vector3& v1, const Vector3& v2);

        inline f32 getX() const { return m_data[0]; }
        inline f32 getY() const { return m_data[1]; }
        inline f32 getZ() const { return m_data[2]; }

        inline f32 setX(f32 x) { return m_data[0] = x; }
        inline f32 setY(f32 y) { return m_data[1] = y; }
        inline f32 setZ(f32 z) { return m_data[2] = z; }

        void set(const Vector3& vec);
        void set(const Vector2& vec, f32 z);
        void set(f32 x, f32 y, f32 z);

        f32* unpack() { return &m_data[0]; }

        static Vector3 zero() { return Vector3(0.f, 0.f, 0.f); }
        static Vector3 one() { return Vector3(1.f, 1.f, 1.f); }
        static Vector3 right() { return Vector3(1.f, 0.f, 0.f); }
        static Vector3 left() { return Vector3(-1.f, 0.f, 0.f); }
        static Vector3 up() { return Vector3(0.f, 1.f, 0.f); }
        static Vector3 down() { return Vector3(0.f, -1.f, 0.f); }
        static Vector3 forward() { return Vector3(0.f, 0.f, -1.f); }
        static Vector3 back() { return Vector3(0.f, 0.f, 1.f); }

        static const Vector3 ZERO;
        static const Vector3 ONE;
        static const Vector3 RIGHT;
        static const Vector3 LEFT;
        static const Vector3 UP;
        static const Vector3 DOWN;
        static const Vector3 FORWARD;
        static const Vector3 BACKWARD;

    private:
        f32 m_data[3];
    };

    inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY(), lhs.getZ() + rhs.getZ());
    }

    inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY(), lhs.getZ() - rhs.getZ());
    }

    inline Vector3 operator-(const Vector3& vec)
    {
        return Vector3(-vec.getX(), -vec.getY(), -vec.getZ());
    }

    inline Vector3 operator*(const Vector3& lhs, const f32& rhs)
    {
        return Vector3(lhs.getX() * rhs, lhs.getY() * rhs, lhs.getZ() * rhs);
    }

    inline Vector3 operator*(const f32& lhs, const Vector3& rhs)
    {
        return Vector3(rhs.getX() * lhs, rhs.getY() * lhs, rhs.getZ() * lhs);
    }

    inline Vector3 operator/(const Vector3& lhs, const f32& rhs)
    {
        return Vector3(lhs.getX() / rhs, lhs.getY() / rhs, lhs.getZ() / rhs);
    }
}

#endif
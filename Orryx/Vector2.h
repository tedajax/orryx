#ifndef ORRYX_VECTOR2_H
#define ORRYX_VECTOR2_H

#include "OrryxTypes.h"
#include "OrryxMath.h"

#include <cmath>

namespace orx
{
    class Vector2
    {
    public:
        Vector2();
        Vector2(f32 x, f32 y);
        Vector2(const Vector2& other);

        Vector2& operator=(const Vector2& rhs);
        Vector2& operator+=(const Vector2& rhs);
        Vector2& operator-=(const Vector2& rhs);
        Vector2& operator*=(const f32& rhs);
        Vector2& operator/=(const f32& rhs);

        bool operator==(const Vector2& rhs) const;
        bool operator!=(const Vector2& rhs) const;

        Vector2& normalize();
        Vector2& negate();
        f32 length() const;
        f32 lengthSqr() const;
        
        static Vector2 normalize(const Vector2& vec);
        static Vector2 negate(const Vector2& vec);
        static f32 length(const Vector2& vec);
        static f32 lengthSqr(const Vector2& vec);

        static Vector2 zero() { return Vector2(0.f, 0.f); }
        static Vector2 one() { return Vector2(1.f, 1.f); }
        static Vector2 unitX() { return Vector2(1.f, 0.f); }
        static Vector2 unitY() { return Vector2(0.f, 1.f); }

        f32 getX() const { return m_data[0]; }
        f32 getY() const { return m_data[1]; }

        f32 setX(f32 x) { return m_data[0] = x; }
        f32 setY(f32 y) { return m_data[1] = y; }

        void set(f32 x, f32 y)
        {
            m_data[0] = x;
            m_data[1] = y;
        }

        f32* unpack() { return &m_data[0]; }

        static const Vector2 ZERO;
        static const Vector2 ONE;
        static const Vector2 UNIT_X;
        static const Vector2 UNIT_Y;
    private:
        f32 m_data[2];
    };

    inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
    {
        return Vector2(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY());
    }

    inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
    {
        return Vector2(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY());
    }

    inline Vector2 operator-(const Vector2& vec)
    {
        return Vector2(-vec.getX(), -vec.getY());
    }

    inline Vector2 operator*(const Vector2& lhs, const f32& rhs)
    {
        return Vector2(lhs.getX() * rhs, lhs.getY() * rhs);
    }

    inline Vector2 operator*(const f32& lhs, const Vector2& rhs)
    {
        return Vector2(rhs.getX() * lhs, rhs.getY() * lhs);
    }

    inline Vector2 operator/(const Vector2& lhs, const f32& rhs)
    {
        return Vector2(lhs.getX() / rhs, lhs.getY() / rhs);
    }
}

#endif
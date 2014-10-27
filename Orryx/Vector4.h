#ifndef ORRYX_VECTOR4_H
#define ORRYX_VECTOR4_H

#include "OrryxTypes.h"
#include "OrryxMath.h"

#include <xmmintrin.h>

namespace orx
{
    typedef __m128 float4;

    class Vector2;
    class Vector3;

    /* Don't use this shit yet not sure how I want to handle some things, use Vector3 */

    class Vector4
    {
        Vector4();
        Vector4(float4 packedData);
        Vector4(f32 x, f32 y, f32 z, f32 w = 0.f);
        Vector4(const Vector2& vec, f32 z = 0.f, f32 w = 0.f);
        Vector4(const Vector3& vec, f32 w = 0.f);
        Vector4(const Vector4& other);

        Vector4& operator=(const Vector4& rhs);
        Vector4& operator+=(const Vector4& rhs);
        Vector4& operator-=(const Vector4& rhs);
        Vector4& operator*=(const f32& rhs);
        Vector4& operator/=(const f32& rhs);

        bool operator==(const Vector4& rhs) const;
        bool operator!=(const Vector4& rhs) const;

        Vector4& normalize();
        Vector4& negate();
        f32 length() const;
        f32 lengthSqr() const;
        f32 dot(const Vector4& vec) const;
        Vector4& cross(const Vector4& vec) const;

        f32 getX() const;
        f32 getY() const;
        f32 getZ() const;
        f32 getW() const;

        f32 setX(const f32& x);
        f32 setY(const f32& y);
        f32 setZ(const f32& z);
        f32 setW(const f32& w);

        void set(const Vector4& vec);
        void set(const Vector3& vec, f32 w);
        void set(const Vector2& vec, f32 z, f32 w);
        void set(f32 x, f32 y, f32 z, f32 w);

        f32* unpack() const;

        friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
        friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
        friend Vector4 operator-(const Vector4& vec);
        friend Vector4 operator*(const Vector4& lhs, const f32& rhs);
        friend Vector4 operator/(const Vector4& lhs, const f32& rhs);
    private:
        float4 m_data;
    };

    inline Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(_mm_add_ss(lhs.m_data, rhs.m_data));
    }

    inline Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(_mm_sub_ss(lhs.m_data, rhs.m_data));
    }

    inline Vector4 operator-(const Vector4& vec)
    {
        float neg1 = -1.f;
        float4 neg = _mm_load1_ps(&neg1);
        return Vector4(_mm_mul_ss(vec.m_data, neg));
    }

    inline Vector4 operator*(const Vector4& lhs, const f32& rhs)
    {
        float4 rhsm = _mm_load1_ps(&rhs);
        return Vector4(_mm_mul_ss(lhs.m_data, rhsm));
    }

    inline Vector4 operator/(const Vector4& lhs, const f32& rhs)
    {
        float4 rhsm = _mm_load1_ps(&rhs);
        return Vector4(_mm_div_ss(lhs.m_data, rhsm));
    }
}
#endif
#ifndef ORRYX_VECTOR3_H
#define ORRYX_VECTOR3_H

#include "OrryxTypes.h"
#include "OrryxMath.h"

#include <string>
#include <cassert>

#include <DirectXMath.h>

using namespace DirectX;

namespace orx
{
    class Matrix;
    class Quaternion;
    
    struct Vector2 
    { 
        Vector2(f32 _x, f32 _y) : x(_x), y(_y) {}
        f32 x, y;
    };
    
    struct Vector3 
    { 
        Vector3(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z) {}
        f32 x, y, z;
    };

    struct Vector4
    {
        Vector4(f32 _x, f32 _y, f32 _z, f32 _w) : x(_x), y(_y), z(_z), w(_w) {}
        f32 x, y, z, w;
    };

    class Vector
    {
    public:
        Vector();
        Vector(f32 x, f32 y, f32 z, f32 w = 0.f);
        Vector(Vector2 vec, f32 z = 0.f, f32 w = 0.f);
        Vector(Vector3 vec, f32 w = 0.f);
        Vector(Vector4 vec);
        Vector(const XMVECTOR& xmvector);
        Vector(const Vector& other);

        Vector& operator=(const Vector& rhs);
        Vector& operator+=(const Vector& rhs);
        Vector& operator-=(const Vector& rhs);
        Vector& operator*=(const f32& rhs);
        Vector& operator*=(const Vector& rhs);
        Vector& operator/=(const f32& rhs);

        f32 operator[](const int i) const
        { 
            assert(i >= 0 && i < 4);
            XMFLOAT4 fvec;
            XMStoreFloat4(&fvec, m_vector);
            switch (i)
            {
            default:
            case 0:
                return fvec.x;

            case 1:
                return fvec.y;

            case 2:
                return fvec.z;

            case 3:
                return fvec.w;
            }
        }

        f32 get(const int i) const
        {
            return (*this)[i];
        }

        f32 set(const int i, const f32 value)
        {
            assert(i >= 0 && i < 4);

            XMFLOAT4 fvec;
            XMStoreFloat4(&fvec, m_vector);

            switch (i)
            {
            default:
            case 0:
                fvec.x = value;
                break;

            case 1:
                fvec.y = value;
                break;

            case 2:
                fvec.z = value;
                break;

            case 3:
                fvec.w = value;
                break;
            }

            m_vector = XMLoadFloat4(&fvec);

            return value;
        }

        bool operator==(const Vector& rhs) const;
        bool operator!=(const Vector& rhs) const;

        Vector& normalize();
        Vector& negate();
        Vector& clamp(const Vector& min, const Vector& max);
        f32 length() const;
        f32 lengthSqr() const;
        f32 dot(const Vector& vec) const;
        Vector cross(const Vector& vec) const;
        Vector& transform(const Matrix& matrix);
        Vector& transform(const Quaternion& rotation);

        static Vector normalize(const Vector& vec);
        static Vector negate(const Vector& vec);
        static Vector clamp(const Vector& vec, const Vector& min, const Vector& max);
        static Vector lerp(const Vector& start, const Vector& end, const f32& t);
        static f32 length(const Vector& vec);
        static f32 lengthSqr(const Vector& vec);
        static f32 dot(const Vector& v1, const Vector& v2);
        static Vector cross(const Vector& v1, const Vector& v2);
        static Vector transform(const Vector& position, const Matrix& matrix);
        static Vector transform(const Vector& position, const Quaternion& rotation);

        const XMVECTOR& getXMVector() const { return m_vector; }
        const XMFLOAT4 getFloat4() const
        {
            XMFLOAT4 floats;
            XMStoreFloat4(&floats, m_vector);
            return floats;
        }

        inline f32 getX() const { return get(0); }
        inline f32 getY() const { return get(1); }
        inline f32 getZ() const { return get(2); }
        inline f32 getW() const { return get(3); }

        inline f32 setX(f32 x) { return set(0, x); }
        inline f32 setY(f32 y) { return set(1, y); }
        inline f32 setZ(f32 z) { return set(2, z); }
        inline f32 setW(f32 w) { return set(3, w); }

        void set(const XMVECTOR& vec)
        {
            m_vector = vec;
        }

        void set(const Vector& vec)
        {
            set(vec.getXMVector());
        }

        void set(f32 x, f32 y, f32 z, f32 w = 0.f)
        {
            XMFLOAT4 fvec;
            fvec.x = x;
            fvec.y = y;
            fvec.z = z;
            fvec.w = w;
            m_vector = XMLoadFloat4(&fvec);
        }

        static const Vector zero() { return Vector(0.f, 0.f, 0.f); }
        static const Vector one() { return Vector(1.f, 1.f, 1.f); }
        static const Vector right() { return Vector(1.f, 0.f, 0.f); }
        static const Vector left() { return Vector(-1.f, 0.f, 0.f); }
        static const Vector up() { return Vector(0.f, 1.f, 0.f); }
        static const Vector down() { return Vector(0.f, -1.f, 0.f); }
        static const Vector forward() { return Vector(0.f, 0.f, -1.f); }
        static const Vector back() { return Vector(0.f, 0.f, 1.f); }
        static const Vector unitX() { return Vector(1.f, 0.f, 0.f); }
        static const Vector unitY() { return Vector(0.f, 1.f, 0.f); }
        static const Vector unitZ() { return Vector(0.f, 0.f, 1.f); }
        static const Vector unitW() { return Vector(0.f, 0.f, 0.f, 1.f); }

        static const Vector cZero;
        static const Vector cOne;
        static const Vector cRight;
        static const Vector cLeft;
        static const Vector cUp;
        static const Vector cDown;
        static const Vector cForward;
        static const Vector cBackward;
        static const Vector cUnitX;
        static const Vector cUnitY;
        static const Vector cUnitZ;
        static const Vector cUnitW;

        std::string toString() const;

    private:
        XMVECTOR m_vector;
    };

    inline Vector operator+(const Vector& lhs, const Vector& rhs)
    {
        return Vector(XMVectorAdd(lhs.getXMVector(), rhs.getXMVector()));
    }

    inline Vector operator-(const Vector& lhs, const Vector& rhs)
    {
        return Vector(XMVectorSubtract(lhs.getXMVector(), rhs.getXMVector()));
    }

    inline Vector operator-(const Vector& vec)
    {
        return Vector::negate(vec);
    }

    inline Vector operator*(const Vector& lhs, const f32& rhs)
    {
        return Vector(XMVectorScale(lhs.getXMVector(), rhs));
    }

    inline Vector operator*(const f32& lhs, const Vector& rhs)
    {
        return rhs * lhs;
    }

    inline Vector operator*(const Vector& lhs, const Vector& rhs)
    {
        return Vector(XMVectorMultiply(lhs.getXMVector(), rhs.getXMVector()));
    }

    inline Vector operator/(const Vector& lhs, const f32& rhs)
    {
        return lhs * (1.f / rhs);
    }
}

#endif
#ifndef ORRYX_QUATERNION_H
#define ORRYX_QUATERNION_H

#include "OrryxMath.h"
#include "OrryxTypes.h"

#include <string>
#include <sstream>

#include <DirectXMath.h>

using namespace DirectX;

namespace orx
{
    class Matrix;
    class Vector;

    class Quaternion
    {
    public:
        Quaternion();
        Quaternion(const Quaternion& other);
        Quaternion(f32 x, f32 y, f32 z, f32 w);
        Quaternion(Vector xmvector, f32 scalar);
        Quaternion(const XMVECTOR& xmvector);

        Quaternion& operator=(const Quaternion& rhs);
        Quaternion& operator+=(const Quaternion& rhs);
        Quaternion& operator-=(const Quaternion& rhs);
        Quaternion& operator*=(const Quaternion& rhs);
        Quaternion& operator*=(const f32 rhs);
        Quaternion& operator/=(const f32 rhs);

        bool operator==(const Quaternion& rhs);
        bool operator!=(const Quaternion& rhs);

        Quaternion& normalize();
        Quaternion& conjugate();
        f32 length() const;
        f32 lengthSqr() const;

        static Quaternion normalize(const Quaternion& quaternion);
        static Quaternion conjugate(const Quaternion& quaternion);
        static Quaternion inverse(const Quaternion& quaternion);
        static Quaternion fromAxisAngle(const Vector& axis, f32 angle);
        static Quaternion fromYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll);
        static Quaternion fromRotationMatrix(const Matrix& matrix);
        static Quaternion fromLookAt(const Vector& source, const Vector& target);
        static f32 dot(const Quaternion& q1, const Quaternion& q2);
        static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, f32 t);
        static Quaternion negate(const Quaternion& quaternion);
        static Vector toEuler(const Quaternion& quaternion);

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

        f32 set(const int i, f32 value)
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

        XMVECTOR getXMVector() const { return m_vector; }

        f32 getX() const { return get(0); }
        f32 getY() const { return get(1); }
        f32 getZ() const { return get(2); }
        f32 getW() const { return get(3); }

        f32 setX(f32 x) { return set(0, x); }
        f32 setY(f32 y) { return set(1, y); }
        f32 setZ(f32 z) { return set(2, z); }
        f32 setW(f32 w) { return set(3, w); }

        void set(f32 x = 0.f, f32 y = 0.f, f32 z = 0.f, f32 w = 0.f)
        {
            XMFLOAT4 fvec;
            fvec.x = x;
            fvec.y = y;
            fvec.z = z;
            fvec.w = w;
            m_vector = XMLoadFloat4(&fvec);
        }

        std::string toString() const;

        static Quaternion identity() { return Quaternion(0.f, 0.f, 0.f, 1.f); }
        static const Quaternion IDENTITY;

    private:
        XMVECTOR m_vector;
    };

    inline Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs)
    {
        return Quaternion(XMVectorAdd(lhs.getXMVector(), rhs.getXMVector()));
    }

    inline Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs)
    {
        return Quaternion(XMVectorSubtract(lhs.getXMVector(), rhs.getXMVector()));
    }

    inline Quaternion operator-(const Quaternion& quaternion)
    {
        return Quaternion::negate(quaternion);
    }

    inline Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
    {
        return Quaternion(XMQuaternionMultiply(lhs.getXMVector(), rhs.getXMVector()));
    }

    inline Quaternion operator*(const Quaternion& lhs, const f32 rhs)
    {
        return Quaternion(XMVectorScale(lhs.getXMVector(), rhs));
    }

    inline Quaternion operator/(const Quaternion& lhs, const f32 rhs)
    {
        return lhs * (1.f / rhs);
    }
}

#endif
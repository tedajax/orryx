#include "Quaternion.h"
namespace orx
{
    const Quaternion Quaternion::IDENTITY = Quaternion::identity();

    Quaternion::Quaternion()
    {
        set(0.f, 0.f, 0.f, 1.f);
    }

    Quaternion::Quaternion(const Quaternion& other)
    {
        m_vector = other.getXMVector();
    }

    Quaternion::Quaternion(f32 x, f32 y, f32 z, f32 w)
    {
        set(x, y, z, w);
    }

    Quaternion::Quaternion(Vector vector, f32 scalar)
    {
        set(vector.getX(), vector.getY(), vector.getZ(), scalar);
    }

    Quaternion::Quaternion(const XMVECTOR& xmvector)
    {
        m_vector = xmvector;
    }

    Quaternion& Quaternion::operator=(const Quaternion& rhs)
    {
        m_vector = rhs.getXMVector();
        return *this;
    }

    Quaternion& Quaternion::operator+=(const Quaternion& rhs)
    {
        return *this = *this + rhs;
    }

    Quaternion& Quaternion::operator-=(const Quaternion& rhs)
    {
        return *this = *this - rhs;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& rhs)
    {
        return *this = *this * rhs;
    }

    Quaternion& Quaternion::operator*=(const f32 rhs)
    {
        return *this = *this * rhs;
    }

    Quaternion& Quaternion::operator/=(const f32 rhs)
    {
        return *this = *this / rhs;
    }

    bool Quaternion::operator==(const Quaternion& rhs)
    {
        return XMQuaternionEqual(m_vector, rhs.getXMVector());
    }

    bool Quaternion::operator!=(const Quaternion& rhs)
    {
        return !(*this == rhs);
    }

    Quaternion& Quaternion::normalize()
    {
        m_vector = XMVector4Normalize(m_vector);
        return *this;
    }

    Quaternion& Quaternion::conjugate()
    {
        m_vector = XMQuaternionConjugate(m_vector);
        return *this;
    }

    f32 Quaternion::length() const
    {
        XMVECTOR lenVec = XMQuaternionLength(m_vector);
        XMFLOAT4 fVec;
        XMStoreFloat4(&fVec, lenVec);
        return fVec.x;
    }

    f32 Quaternion::lengthSqr() const
    {
        XMVECTOR lenVec = XMQuaternionLengthSq(m_vector);
        XMFLOAT4 fVec;
        XMStoreFloat4(&fVec, lenVec);
        return fVec.x;
    }

    Quaternion Quaternion::normalize(const Quaternion& quaternion)
    {
        return Quaternion(XMQuaternionNormalize(quaternion.getXMVector()));
    }

    Quaternion Quaternion::conjugate(const Quaternion& quaternion)
    { 
        return Quaternion(XMQuaternionConjugate(quaternion.getXMVector()));
    }

    Quaternion Quaternion::inverse(const Quaternion& quaternion)
    {
        return Quaternion(XMQuaternionInverse(quaternion.getXMVector()));
    }

    Quaternion Quaternion::fromAxisAngle(const Vector& axis, f32 angle)
    {
        return Quaternion(XMQuaternionRotationAxis(axis.getXMVector(), angle));
    }

    Quaternion Quaternion::fromYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll)
    {
        return Quaternion(XMQuaternionRotationRollPitchYaw(yaw, pitch, roll));
    }

    Quaternion Quaternion::fromRotationMatrix(const Matrix& matrix)
    {
        return Quaternion(XMQuaternionRotationMatrix(matrix.getXMMatrix()));
    }

    Quaternion Quaternion::fromLookAt(const Vector& source, const Vector target)
    {
        Vector forward = Vector::normalize(target - source);
        f32 dot = Vector::dot(Vector::FORWARD, forward);

        if (fabs(dot - -1.f) < 0.000001f)
        {
            return Quaternion(Vector::UP, 3.1415926535897932f);
        }

        if (fabs(dot - 1.f) < 0.000001f)
        {
            return Quaternion::IDENTITY;
        }

        f32 angle = acosf(dot);
        Vector axis = Vector::normalize(Vector::cross(Vector::FORWARD, forward));
        return fromAxisAngle(axis, angle);
    }

    f32 Quaternion::dot(const Quaternion& q1, const Quaternion& q2)
    {
        XMVECTOR dotVec = XMQuaternionDot(q1.getXMVector(), q2.getXMVector());
        XMFLOAT4 fDot;
        XMStoreFloat4(&fDot, dotVec);
        return fDot.x;
    }

    Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, f32 t)
    { 
        return Quaternion(XMQuaternionSlerp(q1.getXMVector(), q2.getXMVector(), t));
    }

    Quaternion Quaternion::negate(const Quaternion& quaternion)
    { 
        return Quaternion(XMVectorScale(quaternion.getXMVector(), -1.f));
    }
}
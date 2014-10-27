#include "Vector3.h"

namespace orx
{
    Vector3::Vector3()
    {
        set(0.f, 0.f, 0.f);
    }

    Vector3::Vector3(f32 x, f32 y, f32 z)
    {
        set(x, y, z);
    }

    Vector3::Vector3(const Vector3& other)
    {
        set(other);
    }

    Vector3::Vector3(const Vector2& vec, f32 z /* = 0.f */)
    {
        set(vec, z);
    }

    Vector3& Vector3::operator=(const Vector3& rhs)
    {
        set(rhs);
        return *this;
    }

    Vector3& Vector3::operator+=(const Vector3& rhs)
    {
        m_data[0] += rhs.getX();
        m_data[1] += rhs.getY();
        m_data[2] += rhs.getZ();
        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& rhs)
    {
        m_data[0] -= rhs.getX();
        m_data[1] -= rhs.getY();
        m_data[2] -= rhs.getZ();
        return *this;
    }

    Vector3& Vector3::operator*=(const f32& rhs)
    {
        m_data[0] *= rhs;
        m_data[1] *= rhs;
        m_data[2] *= rhs;
        return *this;
    }

    Vector3& Vector3::operator/=(const f32& rhs)
    {
        m_data[0] /= rhs;
        m_data[1] /= rhs;
        m_data[2] /= rhs;
        return *this;
    }

    bool Vector3::operator==(const Vector3& rhs) const
    {
        return isApproximatelyEqual(getX(), rhs.getX()) &&
               isApproximatelyEqual(getY(), rhs.getY()) &&
               isApproximatelyEqual(getZ(), rhs.getZ());
    }

    bool Vector3::operator!=(const Vector3& rhs) const
    {
        return !(*this == rhs);
    }

    Vector3& Vector3::normalize()
    {
        *this /= length();
        return *this;
    }

    Vector3& Vector3::negate()
    {
        return -(*this);
    }

    Vector3& Vector3::clamp(const Vector3& min, const Vector3& max)
    {
        setX(orx::clamp(getX(), min.getX(), max.getX()));
        setY(orx::clamp(getY(), min.getY(), max.getY()));
        setZ(orx::clamp(getZ(), min.getZ(), max.getZ()));
        return *this;
    }

    f32 Vector3::length() const
    {
        return sqrtf(lengthSqr());
    }

    f32 Vector3::lengthSqr() const
    {
        return getX() * getX() + getY() * getY() + getZ() * getZ();
    }

    f32 Vector3::dot(const Vector3& vec) const
    {
        return getX() * vec.getX() + getY() * vec.getY() + getZ() * vec.getZ();
    }

    Vector3 Vector3::cross(const Vector3& vec) const
    {
        return Vector3(getY()*vec.getZ() - getZ()*vec.getY(),
                       getX()*vec.getZ() - getZ()*vec.getX(),
                       getX()*vec.getY() - getY()*vec.getZ());
    }

    Vector3 Vector3::normalize(const Vector3& vec)
    {
        f32 len = vec.length();
        return Vector3(vec.getX() / len, vec.getY() / len, vec.getZ() / len);
    }

    Vector3 Vector3::negate(const Vector3& vec)
    {
        return -vec;
    }

    Vector3 Vector3::clamp(const Vector3& vec, const Vector3& min, const Vector3& max)
    {
        return Vector3(orx::clamp(vec.getX(), min.getX(), max.getX()),
                       orx::clamp(vec.getY(), min.getY(), max.getY()),
                       orx::clamp(vec.getZ(), min.getZ(), max.getZ()));
    }

    Vector3 Vector3::lerp(const Vector3& start, const Vector3& end, const f32& t)
    {
        return Vector3(orx::lerp(start.getX(), end.getX(), t),
                       orx::lerp(start.getY(), end.getY(), t),
                       orx::lerp(start.getZ(), end.getZ(), t));
    }

    f32 Vector3::length(const Vector3& vec)
    {
        return vec.length();
    }

    f32 Vector3::lengthSqr(const Vector3& vec)
    {
        return vec.lengthSqr();
    }

    f32 Vector3::dot(const Vector3& v1, const Vector3& v2)
    {
        return v1.dot(v2);
    }

    Vector3& Vector3::cross(const Vector3& v1, const Vector3& v2)
    {
        return v1.cross(v2);
    }

    void Vector3::set(const Vector3& vec)
    {
        set(vec.getX(), vec.getY(), vec.getZ());
    }

    void Vector3::set(const Vector2& vec, f32 z)
    {
        set(vec.getX(), vec.getY(), z);
    }

    void Vector3::set(f32 x, f32 y, f32 z)
    {
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
    }
}
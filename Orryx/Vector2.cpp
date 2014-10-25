#include "Vector2.h"

namespace orx
{
    const Vector2 Vector2::ZERO = Vector2::zero();
    const Vector2 Vector2::ONE = Vector2::one();
    const Vector2 Vector2::UNIT_X = Vector2::unitX();
    const Vector2 Vector2::UNIT_Y = Vector2::unitY();

    Vector2::Vector2()
    {
        set(0.f, 0.f);
    }

    Vector2::Vector2(f32 x, f32 y)
    {
        set(x, y);
    }

    Vector2::Vector2(const Vector2& other)
    {
        set(other.getX(), other.getY());
    }

    Vector2& Vector2::operator=(const Vector2& rhs)
    {
        set(rhs.getX(), rhs.getY());
        return *this;
    }

    Vector2& Vector2::operator+=(const Vector2& rhs)
    {
        this->m_data[0] += rhs.getX();
        this->m_data[1] += rhs.getY();
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& rhs)
    {
        this->m_data[0] -= rhs.getX();
        this->m_data[1] -= rhs.getY();
        return *this;
    }

    Vector2& Vector2::operator*=(const f32& rhs)
    {
        this->m_data[0] *= rhs;
        this->m_data[1] *= rhs;
        return *this;
    }

    Vector2& Vector2::operator/=(const f32& rhs)
    {
        this->m_data[0] /= rhs;
        this->m_data[1] /= rhs;
        return *this;
    }

    bool Vector2::operator==(const Vector2& rhs) const
    {
        return isApproximatelyEqual(getX(), rhs.getX()) &&
            isApproximatelyEqual(getY(), rhs.getY());
    }

    bool Vector2::operator!=(const Vector2& rhs) const
    {
        return !(*this == rhs);
    }

    Vector2& Vector2::normalize()
    {
        *this /= length();
        return *this;
    }

    Vector2& Vector2::negate()
    {
        return -(*this);
    }

    f32 Vector2::length() const
    {
        return sqrtf(lengthSqr());
    }

    f32 Vector2::lengthSqr() const
    {
        return (getX() * getX() + getY() * getY());
    }

    f32 Vector2::dot(const Vector2& vec) const
    {
        return getX() * vec.getX() + getY() * vec.getY();
    }

    Vector2 Vector2::normalize(const Vector2& vec)
    {
        f32 len = vec.length();
        return Vector2(vec.getX() / len, vec.getY() / len);
    }

    Vector2 Vector2::negate(const Vector2& vec)
    {
        return Vector2(-vec.getX(), -vec.getY());
    }

    f32 Vector2::length(const Vector2& vec)
    {
        return sqrtf(Vector2::lengthSqr(vec));
    }

    f32 Vector2::lengthSqr(const Vector2& vec)
    {
        return (vec.getX() * vec.getX() + vec.getY() * vec.getY());
    }

    f32 Vector2::dot(const Vector2& v1, const Vector2& v2)
    {
        return v1.dot(v2);
    }
}
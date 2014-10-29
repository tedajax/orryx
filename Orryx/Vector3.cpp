#include "Vector3.h"

#include <sstream>

namespace orx
{
    const Vector3 Vector3::ZERO = Vector3::zero();
    const Vector3 Vector3::ONE = Vector3::one();
    const Vector3 Vector3::RIGHT = Vector3::right();
    const Vector3 Vector3::LEFT = Vector3::left();
    const Vector3 Vector3::UP = Vector3::up();
    const Vector3 Vector3::DOWN = Vector3::down();
    const Vector3 Vector3::FORWARD = Vector3::forward();
    const Vector3 Vector3::BACKWARD = Vector3::back();

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
                       getX()*vec.getY() - getY()*vec.getX());
    }

    Vector3& Vector3::transform(const Matrix& matrix)
    {
        *this = Vector3::transform(*this, matrix);
        return *this;
    }

    Vector3& Vector3::transform(const Quaternion& rotation)
    {
        *this = Vector3::transform(*this, rotation);
        return *this;
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

    Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2)
    {
        return v1.cross(v2);
    }

    Vector3 Vector3::transform(const Vector3& position, const Matrix& matrix)
    {
        return Vector3(position[0] * matrix(1, 1) + position[1] * matrix(2, 1) + position[2] * matrix(3, 1) + matrix(4, 1),
                       position[0] * matrix(1, 2) + position[1] * matrix(2, 2) + position[2] * matrix(3, 2) + matrix(4, 2),
                       position[0] * matrix(1, 3) + position[1] * matrix(2, 3) + position[2] * matrix(3, 3) + matrix(4, 3));
    }

    Vector3 Vector3::transform(const Vector3& position, const Quaternion& rotation)
    {
        f32 xx = rotation.getX() * rotation.getX();
        f32 yy = rotation.getY() * rotation.getY();
        f32 zz = rotation.getZ() * rotation.getZ();
        f32 wxx = rotation.getW() * xx;
        f32 wyy = rotation.getW() * yy;
        f32 wzz = rotation.getW() * zz;
        f32 xxx = rotation.getX() * xx;
        f32 xyy = rotation.getX() * yy;
        f32 xzz = rotation.getX() * zz;
        f32 yyy = rotation.getY() * yy;
        f32 yzz = rotation.getY() * zz;
        f32 zzz = rotation.getZ() * zz;

        return Vector3(position.getX() * (1.f - yyy - zzz) + position.getY() * (xyy - wzz) + position.getZ() * (xzz + wyy),
                       position.getX() * (xyy + wzz) + position.getY() * (1.f - xxx - zzz) + position.getZ() * (yzz - wxx),
                       position.getX() * (xzz - wyy) + position.getY() * (yzz + wxx) + position.getZ() * (1.f - xxx - yyy));
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

    std::string Vector3::toString() const
    {
        std::stringstream stream;
        stream.precision(2);
        stream << "<" << getX() << ", " << getY() << ", " << getZ() << ">";
        return stream.str();
    }
}
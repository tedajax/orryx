#include "Vector.h"

#include <sstream>

namespace orx
{
    const Vector Vector::cZero = Vector::zero();
    const Vector Vector::cOne = Vector::one();
    const Vector Vector::cRight = Vector::right();
    const Vector Vector::cLeft = Vector::left();
    const Vector Vector::cUp = Vector::up();
    const Vector Vector::cDown = Vector::down();
    const Vector Vector::cForward = Vector::forward();
    const Vector Vector::cBackward = Vector::back();
    const Vector Vector::cUnitX = Vector::unitX();
    const Vector Vector::cUnitY = Vector::unitY();
    const Vector Vector::cUnitZ = Vector::unitZ();
    const Vector Vector::cUnitW = Vector::unitW();

    Vector::Vector()
    {
        set(0.f, 0.f, 0.f, 0.f);
    }

    Vector::Vector(f32 x, f32 y, f32 z, f32 w /* = 0.f */)
    {
        set(x, y, z, w);
    }

    Vector::Vector(Vector2 vec, f32 z /* = 0.f */, f32 w /* = 0.f */)
    {
        set(vec.x, vec.y, z, w);
    }

    Vector::Vector(Vector3 vec, f32 w /* = 0.f */)
    {
        set(vec.x, vec.y, vec.z, w);
    }

    Vector::Vector(Vector4 vec)
    {
        set(vec.x, vec.y, vec.z, vec.w);
    }

    Vector::Vector(const XMVECTOR& xmvector)
    {
        m_vector = xmvector;
    }

    Vector::Vector(const Vector& other)
    {
        set(other);
    }    

    Vector& Vector::operator=(const Vector& rhs)
    {
        set(rhs);
        return *this;
    }

    Vector& Vector::operator+=(const Vector& rhs)
    {
        return *this = *this + rhs;
    }

    Vector& Vector::operator-=(const Vector& rhs)
    {
        return *this = *this - rhs;
    }

    Vector& Vector::operator*=(const f32& rhs)
    {
        return *this = *this * rhs;
    }

    Vector& Vector::operator*=(const Vector& rhs)
    {
        return *this = *this * rhs;
    }

    Vector& Vector::operator/=(const f32& rhs)
    {
        return *this = *this / rhs;
    }

    bool Vector::operator==(const Vector& rhs) const
    {
        XMVECTOR equVec = XMVectorEqual(m_vector, rhs.getXMVector());
        XMFLOAT4 fEqu;
        XMStoreFloat4(&fEqu, equVec);

        return fEqu.x && fEqu.y && fEqu.z && fEqu.w;
    }

    bool Vector::operator!=(const Vector& rhs) const
    {
        return !(*this == rhs);
    }

    Vector& Vector::normalize()
    {
        m_vector = XMVector4Normalize(m_vector);
        return *this;
    }

    Vector& Vector::negate()
    {
        return -(*this);
    }

    Vector& Vector::clamp(const Vector& min, const Vector& max)
    {
        m_vector = XMVectorClamp(m_vector, min.getXMVector(), max.getXMVector());
        return *this;
    }

    f32 Vector::length() const
    {
        XMVECTOR vecLen = XMVector3Length(m_vector);
        XMFLOAT4 fLen;
        XMStoreFloat4(&fLen, vecLen);
        return fLen.x;
    }

    f32 Vector::lengthSqr() const
    {
        XMVECTOR vecLen = XMVector3LengthSq(m_vector);
        XMFLOAT4 fLen;
        XMStoreFloat4(&fLen, vecLen);
        return fLen.x;
    }

    f32 Vector::dot(const Vector& vec) const
    {
        XMVECTOR vecDot = XMVector3Dot(m_vector, vec.getXMVector());
        XMFLOAT4 fDot;
        XMStoreFloat4(&fDot, vecDot);
        return fDot.x;
    }

    Vector Vector::cross(const Vector& vec) const
    {
        return Vector(XMVector3Cross(m_vector, vec.getXMVector()));
    }

    Vector& Vector::transform(const Matrix& matrix)
    {
        m_vector = XMVector3Transform(m_vector, matrix.getXMMatrix());
        return *this;
    }

    Vector& Vector::transform(const Quaternion& rotation)
    {
        return transform(Matrix::fromQuaternion(rotation));
    }

    Vector Vector::normalize(const Vector& vec)
    {
        return Vector(XMVector3Normalize(vec.getXMVector()));
    }

    Vector Vector::negate(const Vector& vec)
    {
        return -vec;
    }

    Vector Vector::clamp(const Vector& vec, const Vector& min, const Vector& max)
    {
        return Vector(XMVectorClamp(vec.getXMVector(), min.getXMVector(), max.getXMVector()));
    }

    Vector Vector::lerp(const Vector& start, const Vector& end, const f32& t)
    {
        return Vector(XMVectorLerp(start.getXMVector(), end.getXMVector(), t));
    }

    f32 Vector::length(const Vector& vec)
    {
        return vec.length();
    }

    f32 Vector::lengthSqr(const Vector& vec)
    {
        return vec.lengthSqr();
    }

    f32 Vector::dot(const Vector& v1, const Vector& v2)
    {
        return v1.dot(v2);
    }

    Vector Vector::cross(const Vector& v1, const Vector& v2)
    {
        return v1.cross(v2);
    }

    Vector Vector::transform(const Vector& position, const Matrix& matrix)
    {
        return Vector(XMVector3Transform(position.getXMVector(), matrix.getXMMatrix()));
    }

    Vector Vector::transform(const Vector& position, const Quaternion& rotation)
    {
        return Vector::transform(position, Matrix::fromQuaternion(rotation));
    }

    std::string Vector::toString() const
    {
        std::stringstream stream;
        stream.precision(2);
        stream << "<" << getX() << ", " << getY() << ", " << getZ() << ">";
        return stream.str();
    }
}
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
        set(other.getX(), other.getY(), other.getZ(), other.getW());
    }

    Quaternion::Quaternion(f32 x, f32 y, f32 z, f32 w)
    {
        set(x, y, z, w);
    }

    Quaternion::Quaternion(Vector3 vector, f32 scalar)
    {
        set(vector.getX(), vector.getY(), vector.getZ(), scalar);
    }

    Quaternion& Quaternion::operator=(const Quaternion& rhs)
    {
        set(rhs.getX(), rhs.getY(), rhs.getZ(), rhs.getW());
        return *this;
    }

    Quaternion& Quaternion::operator+=(const Quaternion& rhs)
    {
        setX(getX() + rhs.getX());
        setY(getY() + rhs.getY());
        setZ(getZ() + rhs.getZ());
        setW(getW() + rhs.getW());
        return *this;
    }

    Quaternion& Quaternion::operator-=(const Quaternion& rhs)
    {
        setX(getX() - rhs.getX());
        setY(getY() - rhs.getY());
        setZ(getZ() - rhs.getZ());
        setW(getW() - rhs.getW());
        return *this;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& rhs)
    {
        f32 x1 = getX();
        f32 y1 = getY();
        f32 z1 = getZ();
        f32 w1 = getW();

        f32 x2 = rhs.getX();
        f32 y2 = rhs.getY();
        f32 z2 = rhs.getZ();
        f32 w2 = rhs.getW();

        f32 yzDiff = (y1 * z2) - (z1 * y2);
        f32 xzDiff = (z1 * x2) - (x1 * z2);
        f32 xyDiff = (x1 * y2) - (y1 * x2);
        f32 prodSum = (x1 * x2) + (y1 * y2) + (z1 * z2);

        set((x1 * w2) + (x2 * w1) + yzDiff,
            (y1 * w2) + (y2 * w1) + xzDiff,
            (z1 * w2) + (z2 * w1) + xyDiff,
            w1 * w2 - prodSum);
        
        return *this;
    }

    Quaternion& Quaternion::operator*=(const f32 rhs)
    {
        setX(getX() * rhs);
        setY(getY() * rhs);
        setZ(getZ() * rhs);
        setW(getW() * rhs);
        return *this;
    }

    Quaternion& Quaternion::operator/=(const Quaternion& rhs)
    {
        setX(getX() / rhs.getX());
        setY(getY() / rhs.getY());
        setZ(getZ() / rhs.getZ());
        setW(getW() / rhs.getW());
        return *this;
    }

    bool Quaternion::operator==(const Quaternion& rhs)
    {
        return isApproximatelyEqual(getX(), rhs.getX()) &&
               isApproximatelyEqual(getY(), rhs.getY()) &&
               isApproximatelyEqual(getZ(), rhs.getZ()) &&
               isApproximatelyEqual(getW(), rhs.getW());
    }

    bool Quaternion::operator!=(const Quaternion& rhs)
    {
        return !(*this == rhs);
    }

    Quaternion& Quaternion::normalize()
    {
        f32 invSqrLen = 1.f / length();
        *this *= invSqrLen;
        return *this;
    }

    Quaternion& Quaternion::conjugate()
    {
        setX(-getX());
        setY(-getY());
        setZ(-getZ());
        return *this;
    }

    f32 Quaternion::length() const
    {
        return sqrtf(lengthSqr());
    }

    f32 Quaternion::lengthSqr() const
    {
        return orx::sqrf(getX()) + orx::sqrf(getY()) + orx::sqrf(getZ()) + orx::sqrf(getW());
    }

    Quaternion Quaternion::normalize(const Quaternion& quaternion)
    {
        Quaternion result(quaternion);
        result *= (1.f / result.length());
        return result;
    }

    Quaternion Quaternion::conjugate(const Quaternion& quaternion)
    { 
        Quaternion result(quaternion);
        result.setX(-result.getX());
        result.setY(-result.getY());
        result.setZ(-result.getZ());
        return result;
    }

    Quaternion Quaternion::inverse(const Quaternion& quaternion)
    {
        Quaternion result(quaternion);
        f32 invLenSqr = 1.f / result.lengthSqr();
        result.setX(-result.getX() * invLenSqr);
        result.setY(-result.getY() * invLenSqr);
        result.setZ(-result.getZ() * invLenSqr);
        result.setW(result.getW() * invLenSqr);
        return result;
    }

    Quaternion Quaternion::fromAxisAngle(const Vector3& axis, f32 angle)
    {
        Quaternion quaternion;
        f32 halfAngle = angle * 0.5f;
        f32 sinAngle = sinf(halfAngle);
        f32 cosAngle = cosf(halfAngle);
        quaternion.setX(axis.getX() * sinAngle);
        quaternion.setY(axis.getY() * sinAngle);
        quaternion.setZ(axis.getZ() * sinAngle);
        quaternion.setW(cosAngle);
        return quaternion;
    }

    Quaternion Quaternion::fromYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll)
    {
        f32 halfYaw = 0.5f * yaw;
        f32 halfPitch = 0.5f * pitch;
        f32 halfRoll = 0.5f * roll;

        f32 yawSin = sinf(halfYaw);
        f32 yawCos = sinf(halfYaw);

        f32 pitchSin = sinf(halfPitch);
        f32 pitchCos = cosf(halfPitch);

        f32 rollSin = sinf(halfRoll);
        f32 rollCos = cosf(halfRoll);

        return Quaternion(yawCos * pitchSin * rollCos + yawSin * pitchCos * rollSin,
            yawSin * pitchCos * rollCos + yawCos * pitchSin * rollSin,
            yawCos * pitchCos * rollSin + yawSin * pitchSin * rollCos,
            yawCos * pitchCos * rollCos + yawSin * pitchSin * rollSin);
    }

    Quaternion Quaternion::fromRotationMatrix(const Matrix& matrix)
    {
        Quaternion quaternion;

        f32 diagSum = matrix(1, 1) + matrix(2, 2) + matrix(3, 3);
        if (diagSum > 0.f)
        {
            f32 sumSqrt = sqrtf(1.f + diagSum);
            quaternion.setW(sumSqrt * 0.5f);
            sumSqrt = 0.5f / sumSqrt;
            quaternion.setX((matrix(2, 3) - matrix(3, 2)) * sumSqrt);
            quaternion.setY((matrix(3, 1) - matrix(1, 3)) * sumSqrt);
            quaternion.setZ((matrix(1, 2) - matrix(2, 1)) * sumSqrt);
            return quaternion;
        }

        if (matrix(1, 1) >= matrix(2, 2) && matrix(1, 1) >= matrix(3, 3))
        {
            f32 sumSqrt = sqrtf(1.f + matrix(1, 1) - matrix(2, 2) - matrix(3, 3));
            quaternion.setX(0.5f * sumSqrt);
            sumSqrt = 0.5f / sumSqrt;
            quaternion.setY((matrix(1, 2) + matrix(2, 1)) * sumSqrt);
            quaternion.setZ((matrix(1, 3) + matrix(3, 1)) * sumSqrt);
            quaternion.setW((matrix(2, 3) + matrix(3, 2)) * sumSqrt);
            return quaternion;
        }

        if (matrix(2, 2) > matrix(3, 3))
        {
            f32 sumSqrt = sqrtf(1.f + matrix(2, 2) - matrix(1, 1) - matrix(3, 3));
            quaternion.setY(0.5f * sumSqrt);
            sumSqrt = 0.5f / sumSqrt;
            quaternion.setX((matrix(2, 1) + matrix(1, 2)) * sumSqrt);
            quaternion.setZ((matrix(3, 2) + matrix(2, 3)) * sumSqrt);
            quaternion.setW((matrix(3, 1) + matrix(1, 3)) * sumSqrt);
            return quaternion;
        }

        f32 sumSqrt = sqrtf(1.f + matrix(3, 3) - matrix(1, 1) - matrix(2, 2));
        quaternion.setZ(sumSqrt * 0.5f);
        sumSqrt = 0.5f / sumSqrt;
        quaternion.setX((matrix(3, 1) + matrix(1, 3)) * sumSqrt);
        quaternion.setY((matrix(3, 2) + matrix(2, 3)) * sumSqrt);
        quaternion.setW((matrix(1, 2) + matrix(2, 1)) * sumSqrt);
        return quaternion;
    }

    Quaternion Quaternion::fromLookAt(const Vector3& source, const Vector3 target)
    {
        Vector3 forward = Vector3::normalize(target - source);
        f32 dot = Vector3::dot(Vector3::FORWARD, forward);

        if (fabs(dot - -1.f) < 0.000001f)
        {
            return Quaternion(Vector3::UP, 3.1415926535897932f);
        }

        if (fabs(dot - 1.f) < 0.000001f)
        {
            return Quaternion::IDENTITY;
        }

        f32 angle = acosf(dot);
        Vector3 axis = Vector3::normalize(Vector3::cross(Vector3::FORWARD, forward));
        return fromAxisAngle(axis, angle);
    }

    f32 Quaternion::dot(const Quaternion& q1, const Quaternion& q2)
    {
        return q1.getX() * q2.getX() + q1.getY() * q2.getY() + q1.getZ() * q2.getZ() + q1.getW() * q2.getW();
    }

    Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, f32 t)
    { 
        f32 q1Scalar;
        f32 q2Scalar;
        f32 product = Quaternion::dot(q1, q2);
        bool dotLTZero = false;

        if (product < 0.f)
        {
            dotLTZero = true;
            product = -product;
        }

        if (product > 0.999999f)
        {
            q1Scalar = 1.f - t;
            q2Scalar = dotLTZero ? -t : t;
        }
        else
        {
            f32 productAcos = acosf(product);
            f32 invSinProduct = 1.f / sinf(productAcos);
            q1Scalar = sinf((1.f - t) * productAcos);
            q2Scalar = dotLTZero ? -sinf(t * productAcos) * invSinProduct : sin(t * productAcos) * invSinProduct;
        }

        return (q1 * q1Scalar) + (q2 * q2Scalar);
    }

    Quaternion Quaternion::lerp(const Quaternion& q1, const Quaternion& q2, f32 t)
    { 
        f32 invT = 1.f - t;
        Quaternion quaternion;
        f32 dotProduct = Quaternion::dot(q1, q2);
        if (dotProduct >= 0.f)
        {
            quaternion.setX(invT * q1.getX() + t * q2.getX());
            quaternion.setY(invT * q1.getY() + t * q2.getY());
            quaternion.setZ(invT * q1.getZ() + t * q2.getZ());
            quaternion.setW(invT * q1.getW() + t * q2.getW());
        }
        else
        {
            quaternion.setX(invT * q1.getX() - t * q2.getX());
            quaternion.setY(invT * q1.getY() - t * q2.getY());
            quaternion.setZ(invT * q1.getZ() - t * q2.getZ());
            quaternion.setW(invT * q1.getW() - t * q2.getW());
        }
        f32 invSqrt = 1.f / sqrtf(quaternion.lengthSqr());
        quaternion *= invSqrt;
        return quaternion;
    }

    Quaternion Quaternion::negate(const Quaternion& quaternion)
    { 
        return Quaternion(-quaternion.getX(),
                          -quaternion.getY(),
                          -quaternion.getZ(),
                          -quaternion.getW());
    }
}
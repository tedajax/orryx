#include "Matrix.h"

#include <sstream>

namespace orx
{
    const Matrix Matrix::IDENTITY = Matrix::identity();

    Matrix::Matrix()
    {
        m_data[0] = 1.f;
        m_data[1] = 0.f;
        m_data[2] = 0.f;
        m_data[3] = 0.f;

        m_data[4] = 0.f;
        m_data[5] = 1.f;
        m_data[6] = 0.f;
        m_data[7] = 0.f;

        m_data[8] = 0.f;
        m_data[9] = 0.f;
        m_data[10] = 1.f;
        m_data[11] = 0.f;

        m_data[12] = 0.f;
        m_data[13] = 0.f;
        m_data[14] = 0.f;
        m_data[15] = 1.f;
    }

    Matrix::Matrix(const Matrix& other)
    {
        for (int i = 0; i < 16; ++i)
        {
            m_data[i] = other[i];
        }
    }

    Matrix::Matrix(f32 m11, f32 m12, f32 m13, f32 m14,
                   f32 m21, f32 m22, f32 m23, f32 m24,
                   f32 m31, f32 m32, f32 m33, f32 m34,
                   f32 m41, f32 m42, f32 m43, f32 m44)
    {
        m_data[0]  = m11;
        m_data[1]  = m12;
        m_data[2]  = m13;
        m_data[3]  = m14;

        m_data[4]  = m21;
        m_data[5]  = m22;
        m_data[6]  = m23;
        m_data[7]  = m24;

        m_data[8]  = m31;
        m_data[9]  = m32;
        m_data[10] = m33;
        m_data[11] = m34;

        m_data[12] = m41;
        m_data[13] = m42;
        m_data[14] = m43;
        m_data[15] = m44;
    }

    Matrix& Matrix::operator=(const Matrix& rhs)
    {
        for (int i = 0; i < 16; ++i)
        {
            m_data[i] = rhs[i];
        }
        return *this;
    }

    Matrix& Matrix::operator+=(const Matrix& rhs)
    {
        for (int i = 0; i < 16; ++i)
        {
            m_data[i] += rhs[i];
        }
        return *this;
    }

    Matrix& Matrix::operator-=(const Matrix& rhs)
    {
        for (int i = 0; i < 16; ++i)
        {
            m_data[i] -= rhs[i];
        }
        return *this;
    }

    Matrix& Matrix::operator*=(const Matrix& rhs)
    {
        Matrix m(*this);
        *this = m * rhs;
        return *this;
    }

    Matrix& Matrix::operator*=(const f32& rhs)
    {
        for (int i = 0; i < 16; ++i)
        {
            m_data[i] *= rhs;
        }
        return *this;
    }

    Matrix& Matrix::operator/=(const Matrix& rhs)
    {
        for (int i = 0; i < 16; ++i)
        {
            m_data[i] /= rhs[i];
        }
        return *this;
    }

    Matrix& Matrix::operator/=(const f32& rhs)
    {
        for (int i = 0; i < 16; ++i)
        {
            m_data[i] /= rhs;
        }
        return *this;
    }

    bool Matrix::operator==(const Matrix& rhs) const
    {
        for (int i = 0; i < 16; ++i)
        {
            if (!isApproximatelyEqual(m_data[i], rhs[i]))
            {
                return false;
            }
        }

        return true;
    }

    bool Matrix::operator!=(const Matrix& rhs) const
    {
        return !(*this == rhs);
    }

    void Matrix::decompose(Vector3& translation, Quaternion& rotation, Vector3& scale)
    {
        //todo
    }

    f32 Matrix::determinant()
    {
        auto m = m_data;
        return
            m[12] * m[9] * m[6] * m[3] - m[8] * m[13] * m[6] * m[3] -
            m[12] * m[5] * m[10] * m[3] + m[4] * m[13] * m[10] * m[3] +
            m[8] * m[5] * m[14] * m[3] - m[4] * m[9] * m[14] * m[3] -
            m[12] * m[9] * m[2] * m[7] + m[8] * m[13] * m[2] * m[7] +
            m[12] * m[1] * m[10] * m[7] - m[0] * m[13] * m[10] * m[7] -
            m[8] * m[1] * m[14] * m[7] + m[0] * m[9] * m[14] * m[7] +
            m[12] * m[5] * m[2] * m[11] - m[4] * m[13] * m[2] * m[11] -
            m[12] * m[1] * m[6] * m[11] + m[0] * m[13] * m[6] * m[11] +
            m[4] * m[1] * m[14] * m[11] - m[0] * m[5] * m[14] * m[11] -
            m[8] * m[5] * m[2] * m[15] + m[4] * m[9] * m[2] * m[15] +
            m[8] * m[1] * m[6] * m[15] - m[0] * m[9] * m[6] * m[15] -
            m[4] * m[1] * m[10] * m[15] + m[0] * m[5] * m[10] * m[15];
    }

    Matrix Matrix::negate(const Matrix& matrix)
    {
        Matrix m;
        for (int i = 0; i < 16; ++i)
        {
            m.set(i, -matrix[i]);
        }
        return m;
    }

    Matrix Matrix::transpose(const Matrix& matrix)
    {
        Matrix m;
        for (int row = 1; row <= 4; ++row)
        {
            for (int col = 1; col <= 4; ++col)
            {
                m.set(col, row, matrix(row, col));
            }
        }
        return m;
    }

    Matrix Matrix::fromRotateAxisAngle(const Vector3& axis, const f32 angle)
    {
        Matrix m;
        f32 x = axis.getX();
        f32 y = axis.getY();
        f32 z = axis.getZ();

        f32 ax = sinf(angle);
        f32 ay = cosf(angle);

        f32 xx = orx::sqrf(x);
        f32 yy = orx::sqrf(y);
        f32 zz = orx::sqrf(z);

        f32 xy = x * y;
        f32 xz = x * z;
        f32 yz = y * z;

        m.set(1, 1, xx + (ay * (1.f - xx)));
        m.set(1, 2, xy - (ay * xy) + (ax * z));
        m.set(1, 3, xy - (ay * xz) - (ax * y));

        m.set(2, 1, xy - (ay * xy) - (ax * z));
        m.set(2, 2, yy + (ay * (1.f - yy)));
        m.set(2, 3, yz - (ay * yz) + (ax * x));

        m.set(3, 1, xz - (ay * xz) + (ax * y));
        m.set(3, 2, yz - (ay * yz) - (ax * x));
        m.set(3, 3, zz + (ay * (1.f - zz)));

        return m;
    }

    Matrix Matrix::fromRotateX(const f32 angle)
    {
        Matrix m;
        float ax = cosf(angle);
        float ay = sinf(angle);
        m.set(2, 2, ax);
        m.set(2, 3, ay);
        m.set(3, 2, -ay);
        m.set(3, 3, ax);
        return m;
    }

    Matrix Matrix::fromRotateY(const f32 angle)
    {
        Matrix m;
        float ax = cosf(angle);
        float ay = sinf(angle);
        m.set(1, 1, ax);
        m.set(1, 3, -ay);
        m.set(3, 1, ay);
        m.set(3, 3, ax);
        return m;
    }
    
    Matrix Matrix::fromRotateZ(const f32 angle)
    {
        Matrix m;
        float ax = cosf(angle);
        float ay = sinf(angle);
        m.set(1, 1, ax);
        m.set(1, 2, ay);
        m.set(2, 1, -ay);
        m.set(2, 2, ax);
        return m;
    }
    
    Matrix Matrix::fromQuaternion(const Quaternion& quaternion)
    {
        Matrix m;
        f32 xx = quaternion.getX() * quaternion.getX();
        f32 yy = quaternion.getY() * quaternion.getY();
        f32 zz = quaternion.getZ() * quaternion.getZ();
        f32 xy = quaternion.getX() * quaternion.getY();
        f32 zw = quaternion.getZ() * quaternion.getW();
        f32 zx = quaternion.getZ() * quaternion.getX();
        f32 yw = quaternion.getY() * quaternion.getW();
        f32 yz = quaternion.getY() * quaternion.getZ();
        f32 xw = quaternion.getX() * quaternion.getW();

        m.set(1, 1, 1.f - (2.f * (yy + zz)));
        m.set(1, 2, 2.f * (xy - zw));
        m.set(1, 3, 2.f * (zx - yw));

        m.set(2, 1, 2.f * (xy - zw));
        m.set(2, 2, 1.f - (2.f * (zz + xx)));
        m.set(2, 3, 2.f * (yz + xw));

        m.set(3, 1, 2.f * (zx + yw));
        m.set(3, 2, 2.f * (yz - xw));
        m.set(3, 3, 1.f - (2.f * (yy + xx)));

        return m;
    }
    
    Matrix Matrix::fromYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll)
    {
        Matrix m;
        Quaternion quaternion = Quaternion::fromYawPitchRoll(yaw, pitch, roll);
        m = Matrix::fromQuaternion(quaternion);
        return m;
    }
    
    Matrix Matrix::createLookAt(const Vector3& position, const Vector3& target, const Vector3& up)
    {
        Matrix m;
        Vector3 v1 = Vector3::normalize(position - target);
        Vector3 v2 = Vector3::normalize(Vector3::cross(v1, up));
        Vector3 v3 = Vector3::cross(v2, v1);

        m.set(1, 1, v2.getX());
        m.set(1, 2, v3.getX());
        m.set(1, 3, v1.getX());

        m.set(2, 1, v2.getY());
        m.set(2, 2, v3.getY());
        m.set(2, 3, v1.getY());

        m.set(3, 1, v2.getZ());
        m.set(3, 2, v3.getZ());
        m.set(3, 3, v1.getZ());

        m.set(4, 1, -Vector3::dot(v2, position));
        m.set(4, 2, -Vector3::dot(v3, position));
        m.set(4, 3, -Vector3::dot(v1, position));

        return m;
    }
    
    Matrix Matrix::createOrthographic(const f32 width, const f32 height, const f32 nearZ, const f32 farZ)
    {
        Matrix m;
        m.set(1, 1, 2.f / width);
        m.set(2, 2, 2.f / height);
        m.set(3, 3, 1.f / (nearZ - farZ));
        m.set(4, 3, nearZ / (nearZ - farZ));
        return m;
    }
    
    Matrix Matrix::createPerspective(const f32 fov, const f32 aspect, const f32 nearZ, const f32 farZ)
    {
        Matrix m;
        f32 tanHalfFov = tanf(fov * 0.5f);
        m.set(1, 1, 1.f / (aspect * tanHalfFov));
        m.set(2, 2, 1.f / tanHalfFov);
        m.set(3, 3, -(farZ + nearZ) / (farZ - nearZ));
        m.set(3, 4, -1.f);
        m.set(4, 3, -(2.f * farZ * nearZ) / (farZ - nearZ));
        m.set(4, 4, 0.f);
        return m;
    }
    
    Matrix Matrix::fromScale(const Vector3& scale)
    {
        Matrix m;
        m.set(1, 1, scale.getX());
        m.set(2, 2, scale.getY());
        m.set(3, 3, scale.getZ());
        return m;
    }
    
    Matrix Matrix::fromScale(const f32 scale)
    {
        Matrix m;
        m.set(1, 1, scale);
        m.set(2, 2, scale);
        m.set(3, 3, scale);
        return m;
    }
    
    Matrix Matrix::fromTranslation(const Vector3& position)
    {
        Matrix m;
        m.set(4, 1, position.getX());
        m.set(4, 2, position.getY());
        m.set(4, 3, position.getZ());
        return m;
    }
    
    Matrix Matrix::fromTranslation(const f32 x, const f32 y, const f32 z)
    {
        Matrix m;
        m.set(4, 1, x);
        m.set(4, 2, y);
        m.set(4, 3, z);
        return m;
    }
    
    Matrix Matrix::world(const Vector3& position, const Vector3& forward, const Vector3& up)
    {
        Matrix m;
        Vector3 v1 = Vector3::normalize(-forward);
        Vector3 v2 = Vector3::normalize(Vector3::cross(up, v1));
        Vector3 v3 = Vector3::cross(v1, v2);

        m.set(1, 1, v2.getX());
        m.set(1, 2, v2.getY());
        m.set(1, 3, v2.getZ());

        m.set(2, 1, v3.getX());
        m.set(2, 2, v3.getY());
        m.set(2, 3, v3.getZ());

        m.set(3, 1, v1.getX());
        m.set(3, 2, v1.getY());
        m.set(3, 3, v1.getZ());

        m.set(4, 1, position.getX());
        m.set(4, 2, position.getY());
        m.set(4, 3, position.getZ());

        return m;
    }
    
    Matrix Matrix::invert(const Matrix& matrix)
    {
        Matrix m;
        f32 m11 = matrix(1, 1);
        f32 m12 = matrix(1, 2);
        f32 m13 = matrix(1, 3);
        f32 m14 = matrix(1, 4);
        f32 m21 = matrix(2, 1);
        f32 m22 = matrix(2, 2);
        f32 m23 = matrix(2, 3);
        f32 m24 = matrix(2, 4);
        f32 m31 = matrix(3, 1);
        f32 m32 = matrix(3, 2);
        f32 m33 = matrix(3, 3);
        f32 m34 = matrix(3, 4);
        f32 m41 = matrix(4, 1);
        f32 m42 = matrix(4, 2);
        f32 m43 = matrix(4, 3);
        f32 m44 = matrix(4, 4);
        f32 det1 = (m33 * m44) - (m34 * m43);
        f32 det2 = (m32 * m44) - (m34 * m42);
        f32 det3 = (m32 * m43) - (m33 * m42);
        f32 det4 = (m31 * m43) - (m33 * m41);
        f32 det5 = (m31 * m44) - (m34 * m41);
        f32 det6 = (m31 * m42) - (m32 * m41);
        f32 det7 = ((m22 * det1) - (m23 * det2)) + (m24 * det3);
        f32 det8 = -(((m21 * det1) - (m23 * det5)) + (m24 * det4));
        f32 det9 = ((m21 * det2) - (m22 * det5)) + (m24 * det6);
        f32 det10 = -(((m21 * det3) - (m22 * det4)) + (m23 * det6));
        f32 invDet = 1.f / ((((m11 * det7) + (m12 * det8)) + (m13 * det9)) + (m14 * det10));
        m.set(1, 1, det7 * invDet);
        m.set(2, 1, det8 * invDet);
        m.set(3, 1, det9 * invDet);
        m.set(4, 1, det10 * invDet);
        m.set(1, 2, -(((m12 * det1) - (m13 * det2)) + (m14 * det3)) * invDet);
        m.set(2, 2, (((m11 * det1) - (m13 * det5)) + (m14 * det4)) * invDet);
        m.set(3, 2, -(((m11 * det2) - (m12 * det5)) + (m14 * det6)) * invDet);
        m.set(4, 2, (((m11 * det3) - (m12 * det4)) + (m13 * det6)) * invDet);
        f32 det11 = (m23 * m44) - (m24 * m43);
        f32 det12 = (m22 * m44) - (m24 * m42);
        f32 det13 = (m22 * m43) - (m23 * m42);
        f32 det14 = (m21 * m44) - (m24 * m41);
        f32 det15 = (m21 * m43) - (m23 * m41);
        f32 det16 = (m21 * m42) - (m22 * m41);
        m.set(1, 3, (((m12 * det11) - (m13 * det12)) + (m14 * det13)) * invDet);
        m.set(2, 3, -(((m11 * det11) - (m13 * det14)) + (m14 * det15)) * invDet);
        m.set(3, 3, (((m11 * det12) - (m12 * det14)) + (m14 * det16)) * invDet);
        m.set(4, 3, -(((m11 * det13) - (m12 * det15)) + (m13 * det16)) * invDet);
        f32 det17 = (m23 * m34) - (m24 * m33);
        f32 det18 = (m22 * m34) - (m24 * m32);
        f32 det19 = (m22 * m33) - (m23 * m32);
        f32 det20 = (m21 * m34) - (m24 * m31);
        f32 det21 = (m21 * m33) - (m23 * m31);
        f32 det22 = (m21 * m32) - (m22 * m31);
        m.set(1, 4, -(((m12 * det17) - (m13 * det18)) + (m14 * det19)) * invDet);
        m.set(2, 4, (((m11 * det17) - (m13 * det20)) + (m14 * det21)) * invDet);
        m.set(3, 4, -(((m11 * det18) - (m12 * det20)) + (m14 * det22)) * invDet);
        m.set(4, 4, (((m11 * det19) - (m12 * det21)) + (m13 * det22)) * invDet);
        return m;
    }
    
    Matrix Matrix::transform(const Matrix& matrix, const Quaternion& rotation)
    {
        Matrix m;

        f32 x2 = rotation.getX() * 2.f;
        f32 y2 = rotation.getY() * 2.f;
        f32 z2 = rotation.getZ() * 2.f;

        f32 wx2 = rotation.getW() * x2;
        f32 wy2 = rotation.getW() * y2;
        f32 wz2 = rotation.getW() * z2;

        f32 xx2 = rotation.getX() * x2;
        f32 xy2 = rotation.getX() * y2;
        f32 xz2 = rotation.getX() * z2;
        f32 yy2 = rotation.getY() * y2;
        f32 yz2 = rotation.getY() * z2;
        f32 zz2 = rotation.getZ() * z2;

        f32 inYZ = 1.f - yy2 - zz2;
        f32 num1 = xy2 - wz2;
        f32 num2 = xz2 + wy2;
        f32 num3 = xy2 + wz2;
        f32 inXZ = 1.f - xx2 - zz2;
        f32 num4 = yz2 - wx2;
        f32 num5 = xz2 - wy2;
        f32 num6 = yz2 + wx2;
        f32 inXY = 1.f - xx2 - yy2;

        m.set(1, 1, matrix(1, 1) * inYZ + matrix(1, 2) * num1 + matrix(1, 3) * num2);
        m.set(1, 2, matrix(1, 1) * num3 + matrix(1, 2) * inXZ + matrix(1, 3) * num4);
        m.set(1, 3, matrix(1, 1) * num5 + matrix(1, 2) * num6 + matrix(1, 3) * inXY);
        m.set(1, 4, matrix(1, 4));

        m.set(2, 1, matrix(2, 1) * inYZ + matrix(2, 2) * num1 + matrix(2, 3) * num2);
        m.set(2, 2, matrix(2, 1) * num3 + matrix(2, 2) * inXZ + matrix(2, 3) * num4);
        m.set(2, 3, matrix(2, 1) * num5 + matrix(2, 2) * num6 + matrix(2, 3) * inXY);
        m.set(2, 4, matrix(2, 4));

        m.set(3, 1, matrix(3, 1) * inYZ + matrix(3, 2) * num1 + matrix(3, 3) * num2);
        m.set(3, 2, matrix(3, 1) * num3 + matrix(3, 2) * inXZ + matrix(3, 3) * num4);
        m.set(3, 3, matrix(3, 1) * num5 + matrix(3, 2) * num6 + matrix(3, 3) * inXY);
        m.set(3, 4, matrix(3, 4));

        m.set(4, 1, matrix(4, 1) * inYZ + matrix(4, 2) * num1 + matrix(4, 3) * num2);
        m.set(4, 2, matrix(4, 1) * num3 + matrix(4, 2) * inXZ + matrix(4, 3) * num4);
        m.set(4, 3, matrix(4, 1) * num5 + matrix(4, 2) * num6 + matrix(4, 3) * inXY);
        m.set(4, 4, matrix(4, 4));

        return m;
    }

    std::string Matrix::toString()
    {
        std::stringstream stream;
        stream.precision(2);
        stream << "| " << get(1, 1) << ",\t" << get(1, 2) << ",\t" << get(1, 3) << ",\t" << get(1, 4) << ", |\n"
               << "| " << get(2, 1) << ",\t" << get(2, 2) << ",\t" << get(2, 3) << ",\t" << get(2, 4) << ", |\n"
               << "| " << get(3, 1) << ",\t" << get(3, 2) << ",\t" << get(3, 3) << ",\t" << get(3, 4) << ", |\n"
               << "| " << get(4, 1) << ",\t" << get(4, 2) << ",\t" << get(4, 3) << ",\t" << get(4, 4) << "  |\n";
        return stream.str();
    }
}

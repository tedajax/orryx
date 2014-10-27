#include "Matrix.h"

namespace orx
{
    const Matrix Matrix::IDENTITY = Matrix::identity();

    Matrix::Matrix()
    {
        Matrix(1.f, 0.f, 0.f, 0.f,
               0.f, 1.f, 0.f, 0.f,
               0.f, 0.f, 1.f, 0.f,
               0.f, 0.f, 0.f, 1.f);
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

    Matrix Matrix::rotateAxisAngle(const Vector3& axis, const f32 angle)
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

    Matrix Matrix::rotateX(const f32 angle)
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

    Matrix Matrix::rotateY(const f32 angle)
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
    
    Matrix Matrix::rotateZ(const f32 angle)
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
    
    Matrix Matrix::rotateQuaternion(const Quaternion& quaternion)
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
    
    Matrix Matrix::rotateYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll)
    {
    }
    
    Matrix Matrix::lookAt(const Vector3& position, const Vector3& target, const Vector3& up)
    {
        Matrix m;
        Vector3 v1 = Vector3::normalize(position - target);
        Vector3 v2 = Vector3::normalize(Vector3::cross(up, v1));
        Vector3 v3 = Vector3::cross(v1, v2);

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
    
    Matrix Matrix::orthographic(const f32 width, const f32 height, const f32 nearZ, const f32 farZ)
    {
        Matrix m;
        m.set(1, 1, 2.f / width);
        m.set(2, 2, 2.f / height);
        m.set(3, 3, 1.f / (nearZ - farZ));
        m.set(4, 3, nearZ / (nearZ - farZ));
        return m;
    }
    
    Matrix Matrix::perspective(const f32 fov, const f32 aspect, const f32 nearZ, const f32 farZ)
    {
        Matrix m;
        f32 fovtan = 1.f / tanf(fov * 0.5f);
        f32 scaledAspect = fovtan / aspect;
        m.set(1, 1, scaledAspect);
        m.set(2, 2, fovtan);
        m.set(3, 3, farZ / (nearZ - farZ));
        m.set(3, 4, -1.f);
        m.set(4, 3, (nearZ * farZ) / (nearZ - farZ));
        m.set(4, 4, 0.f);
        return m;
    }
    
    Matrix Matrix::scale(const Vector3& scale)
    {
        Matrix m;
        m.set(1, 1, scale.getX());
        m.set(2, 2, scale.getY());
        m.set(3, 3, scale.getZ());
        return m;
    }
    
    Matrix Matrix::scale(const f32 scale)
    {
        Matrix m;
        m.set(1, 1, scale);
        m.set(2, 2, scale);
        m.set(3, 3, scale);
        return m;
    }
    
    Matrix Matrix::translate(const Vector3& position)
    {
        Matrix m;
        m.set(4, 1, position.getX());
        m.set(4, 2, position.getY());
        m.set(4, 3, position.getZ());
        return m;
    }
    
    Matrix Matrix::translate(const f32 x, const f32 y, const f32 z)
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
    }
    
    Matrix Matrix::transform(const Matrix& matrix, const Quaternion& rotation)
    {
    }
}

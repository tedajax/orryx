#ifndef ORRYX_MATRIX_H
#define ORRYX_MATRIX_H

#include "OrryxTypes.h"
#include "OrryxMath.h"

namespace orx
{
    class Vector3;
    class Quaternion;

    class Matrix
    {
    public:
        Matrix();
        Matrix(const Matrix& other);
        Matrix(f32 m11, f32 m12, f32 m13, f32 m14,
               f32 m21, f32 m22, f32 m23, f32 m24,
               f32 m31, f32 m32, f32 m33, f32 m34,
               f32 m41, f32 m42, f32 m43, f32 m44);

        Matrix& operator=(const Matrix& rhs);
        Matrix& operator+=(const Matrix& rhs);
        Matrix& operator-=(const Matrix& rhs);
        Matrix& operator*=(const Matrix& rhs);
        Matrix& operator*=(const f32& rhs);
        Matrix& operator/=(const Matrix& rhs);
        Matrix& operator/=(const f32& rhs);

        f32 operator[](const int i) const { return m_data[i]; }

        // row, then col [1..4]
        f32 operator()(const int row, const int col) const
        {
            return m_data[(row - 1) * 4 + (col - 1)];
        }

        bool operator==(const Matrix& rhs) const;
        bool operator!=(const Matrix& rhs) const;

        f32 get(const int row, const int col) { return (*this)(row, col); }
        void set(const int row, const int col, const f32 val)
        {
            m_data[(row - 1) * 4 + (col - 1)] = val;
        }
        void set(const int i, const f32 val)
        {
            m_data[i] = val;
        }

        void decompose(Vector3& translation, Quaternion& rotation, Vector3& scale);
        f32 determinant();

        static Matrix negate(const Matrix& matrix);
        static Matrix transpose(const Matrix& matrix);
        static Matrix rotateAxisAngle(const Vector3& axis, const f32 angle);
        static Matrix rotateX(const f32 angle);
        static Matrix rotateY(const f32 angle);
        static Matrix rotateZ(const f32 angle);
        static Matrix rotateQuaternion(const Quaternion& quaternion);
        static Matrix rotateYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll);
        static Matrix lookAt(const Vector3& position, const Vector3& target, const Vector3& up);
        static Matrix orthographic(const f32 width, const f32 height, const f32 nearZ, const f32 farZ);
        static Matrix perspective(const f32 fov, const f32 aspect, const f32 nearZ, const f32 farZ);
        static Matrix scale(const Vector3& scale);
        static Matrix scale(const f32 scale);
        static Matrix translate(const Vector3& position);
        static Matrix translate(const f32 x, const f32 y, const f32 z);
        static Matrix world(const Vector3& position, const Vector3& forward, const Vector3& up);
        static Matrix invert(const Matrix& matrix);
        static Matrix transform(const Matrix& matrix, const Quaternion& rotation);

        static f32 mulRowCol(const Matrix& lhs, const Matrix& rhs, const int row, const int col)
        {
            f32 result = 0.f;
            for (int i = 0; i < 4; ++i)
            {
                result += lhs(row, i) * rhs(i, col);
            }
            return result;
        }

        f32* unpack() { return &m_data[0]; }

        static Matrix identity()
        { 
            return Matrix(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
        }

        static const Matrix IDENTITY;

    private:
        f32 m_data[16];
    };

    inline Matrix operator+(const Matrix& lhs, const Matrix& rhs)
    {
        Matrix m(lhs);
        m += rhs;
        return m;
    }

    inline Matrix operator-(const Matrix& lhs, const Matrix& rhs)
    {
        Matrix m(lhs);
        m -= rhs;
        return m;
    }

    inline Matrix operator-(const Matrix& mat)
    {
        return Matrix::negate(mat);
    }

    inline Matrix operator*(const Matrix& lhs, const Matrix& rhs)
    {
        Matrix m;
        for (int row = 1; row <= 4; ++row)
        {
            for (int col = 1; col <= 4; ++col)
            {
                m.set(row, col, Matrix::mulRowCol(lhs, rhs, row, col));
            }
        }
        return m;
    }

    inline Matrix operator*(const Matrix& lhs, const f32& rhs)
    {
        Matrix m;
        for (int i = 0; i < 16; ++i)
        {
            m.set(i, lhs[i] * rhs);
        }
        return m;
    }

    inline Matrix operator/(const Matrix& lhs, const Matrix& rhs)
    {
        Matrix m;
        for (int i = 0; i < 16; ++i)
        {
            m.set(i, lhs[i] / rhs[i]);
        }
        return m;
    }

    inline Matrix operator/(const Matrix& lhs, const f32& rhs)
    {
        return lhs * (1.f / rhs);
    }
}

#endif
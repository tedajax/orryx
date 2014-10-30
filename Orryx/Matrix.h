#ifndef ORRYX_MATRIX_H
#define ORRYX_MATRIX_H

#include "OrryxTypes.h"
#include "OrryxMath.h"

#include <string>

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
        f32& operator[](const int i) { return m_data[i]; }

        // row, then col [1..4]
        f32 operator()(const int row, const int col) const
        {
            return m_data[(col - 1) * 4 + (row - 1)];
        }

        f32& operator()(const int row, const int col)
        {
            return m_data[(col - 1) * 4 + (row - 1)];
        }

        bool operator==(const Matrix& rhs) const;
        bool operator!=(const Matrix& rhs) const;

        f32 get(const int row, const int col) { return (*this)(row, col); }
        void set(const int row, const int col, const f32 val)
        {
            m_data[(col - 1) * 4 + (row - 1)] = val;
        }
        void set(const int i, const f32 val)
        {
            m_data[i] = val;
        }

        void decompose(Vector3& translation, Quaternion& rotation, Vector3& scale);
        f32 determinant();

        static Matrix negate(const Matrix& matrix);
        static Matrix transpose(const Matrix& matrix);
        static Matrix fromRotateAxisAngle(const Vector3& axis, const f32 angle);
        static Matrix fromRotateX(const f32 angle);
        static Matrix fromRotateY(const f32 angle);
        static Matrix fromRotateZ(const f32 angle);
        static Matrix fromQuaternion(const Quaternion& quaternion);
        static Matrix fromYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll);
        static Matrix createLookAt(const Vector3& position, const Vector3& target, const Vector3& up);
        static Matrix createOrthographic(const f32 width, const f32 height, const f32 nearZ, const f32 farZ);
        static Matrix createPerspective(const f32 fov, const f32 aspect, const f32 nearZ, const f32 farZ);
        static Matrix fromScale(const Vector3& scale);
        static Matrix fromScale(const f32 scale);
        static Matrix fromTranslation(const Vector3& position);
        static Matrix fromTranslation(const f32 x, const f32 y, const f32 z);
        static Matrix world(const Vector3& position, const Vector3& forward, const Vector3& up);
        static Matrix invert(const Matrix& matrix);
        static Matrix transform(const Matrix& matrix, const Quaternion& rotation);

        static f32 mulRowCol(const Matrix& lhs, const Matrix& rhs, const int row, const int col)
        {
            f32 result = 0.f;
            for (int i = 1; i <= 4; ++i)
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

        std::string toString();

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

        m(1, 1) = lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1) + lhs(1, 4) * rhs(4, 1);
        m(1, 2) = lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2) + lhs(1, 4) * rhs(4, 2);
        m(1, 3) = lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3) + lhs(1, 3) * rhs(3, 3) + lhs(1, 4) * rhs(4, 3);
        m(1, 4) = lhs(1, 1) * rhs(1, 4) + lhs(1, 2) * rhs(2, 4) + lhs(1, 3) * rhs(3, 4) + lhs(1, 4) * rhs(4, 4);

        m(2, 1) = lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1) + lhs(2, 4) * rhs(4, 1);
        m(2, 2) = lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2) + lhs(2, 3) * rhs(3, 2) + lhs(2, 4) * rhs(4, 2);
        m(2, 3) = lhs(2, 1) * rhs(1, 3) + lhs(2, 2) * rhs(2, 3) + lhs(2, 3) * rhs(3, 3) + lhs(2, 4) * rhs(4, 3);
        m(2, 4) = lhs(2, 1) * rhs(1, 4) + lhs(2, 2) * rhs(2, 4) + lhs(2, 3) * rhs(3, 4) + lhs(2, 4) * rhs(4, 4);

        m(3, 1) = lhs(3, 1) * rhs(1, 1) + lhs(3, 2) * rhs(2, 1) + lhs(3, 3) * rhs(3, 1) + lhs(3, 4) * rhs(4, 1);
        m(3, 2) = lhs(3, 1) * rhs(1, 2) + lhs(3, 2) * rhs(2, 2) + lhs(3, 3) * rhs(3, 2) + lhs(3, 4) * rhs(4, 2);
        m(3, 3) = lhs(3, 1) * rhs(1, 3) + lhs(3, 2) * rhs(2, 3) + lhs(3, 3) * rhs(3, 3) + lhs(3, 4) * rhs(4, 3);
        m(3, 4) = lhs(3, 1) * rhs(1, 4) + lhs(3, 2) * rhs(2, 4) + lhs(3, 3) * rhs(3, 4) + lhs(3, 4) * rhs(4, 4);

        m(4, 1) = lhs(4, 1) * rhs(1, 1) + lhs(4, 2) * rhs(2, 1) + lhs(4, 3) * rhs(3, 1) + lhs(4, 4) * rhs(4, 1);
        m(4, 2) = lhs(4, 1) * rhs(1, 2) + lhs(4, 2) * rhs(2, 2) + lhs(4, 3) * rhs(3, 2) + lhs(4, 4) * rhs(4, 2);
        m(4, 3) = lhs(4, 1) * rhs(1, 3) + lhs(4, 2) * rhs(2, 3) + lhs(4, 3) * rhs(3, 3) + lhs(4, 4) * rhs(4, 3);
        m(4, 4) = lhs(4, 1) * rhs(1, 4) + lhs(4, 2) * rhs(2, 4) + lhs(4, 3) * rhs(3, 4) + lhs(4, 4) * rhs(4, 4);

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
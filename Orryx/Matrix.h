#ifndef ORRYX_MATRIX_H
#define ORRYX_MATRIX_H

#include "OrryxTypes.h"
#include "OrryxMath.h"
#include <DirectXMath.h>

#include <string>

using namespace DirectX;

namespace orx
{
    class Vector;
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
        Matrix(const XMMATRIX& xmmatrix);

        Matrix& operator=(const Matrix& rhs);
        Matrix& operator+=(const Matrix& rhs);
        Matrix& operator-=(const Matrix& rhs);
        Matrix& operator*=(const Matrix& rhs);
        Matrix& operator*=(const f32& rhs);
        Matrix& operator/=(const f32& rhs);

        // row, then col [1..4]
        f32 operator()(const int row, const int col) const
        {
            XMVECTOR rowVec = m_matrix.r[row - 1];
            return rowVec.m128_f32[col - 1];
        }

        f32& operator()(const int row, const int col)
        {
            XMVECTOR rowVec = m_matrix.r[row - 1];
            return rowVec.m128_f32[col - 1];
        }

        bool operator==(const Matrix& rhs) const;
        bool operator!=(const Matrix& rhs) const;

        f32 get(const int row, const int col) { return (*this)(row, col); }

        void setMatrix(const Matrix& other)
        {
            m_matrix = other.getXMMatrix();
        }

        void decompose(Vector& translation, Quaternion& rotation, Vector& scale);
        f32 determinant();

        static Matrix negate(const Matrix& matrix);
        static Matrix transpose(const Matrix& matrix);
        static Matrix fromRotateAxisAngle(const Vector& axis, const f32 angle);
        static Matrix fromRotateX(const f32 angle);
        static Matrix fromRotateY(const f32 angle);
        static Matrix fromRotateZ(const f32 angle);
        static Matrix fromQuaternion(const Quaternion& quaternion);
        static Matrix fromYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll);
        static Matrix createLookAt(const Vector& position, const Vector& target, const Vector& up);
        static Matrix createOrthographic(const f32 width, const f32 height, const f32 nearZ, const f32 farZ);
        static Matrix createPerspective(const f32 fov, const f32 aspect, const f32 nearZ, const f32 farZ);
        static Matrix fromScale(const Vector& scale);
        static Matrix fromScale(const f32 scale);
        static Matrix fromTranslation(const Vector& position);
        static Matrix fromTranslation(const f32 x, const f32 y, const f32 z);
        static Matrix world(const Vector& position, const Vector& forward, const Vector& up);
        static Matrix invert(const Matrix& matrix);
        static Matrix transform(const Matrix& matrix, const Quaternion& rotation);

        const XMMATRIX& getXMMatrix() const { return m_matrix; }
        const XMFLOAT4X4 getFloat4x4() const
        {
            XMFLOAT4X4 floats;
            XMStoreFloat4x4(&floats, m_matrix);
            return floats;
        }

        const f32* unpack() { return &getFloat4x4().m[0][0]; }

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
        XMMATRIX m_matrix;
    };

    inline Matrix operator+(const Matrix& lhs, const Matrix& rhs)
    {
        return Matrix(lhs.getXMMatrix() + rhs.getXMMatrix());
    }

    inline Matrix operator-(const Matrix& lhs, const Matrix& rhs)
    {
        return Matrix(lhs.getXMMatrix() - rhs.getXMMatrix());
    }

    inline Matrix operator-(const Matrix& mat)
    {
        return Matrix::negate(mat);
    }

    inline Matrix operator*(const Matrix& lhs, const Matrix& rhs)
    {
        return Matrix(lhs * rhs);
    }

    inline Matrix operator*(const Matrix& lhs, const f32& rhs)
    {
        return Matrix(lhs * rhs);
    }

    inline Matrix operator/(const Matrix& lhs, const f32& rhs)
    {
        return Matrix(lhs / rhs);
    }
}

#endif
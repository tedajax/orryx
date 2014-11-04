#include "Matrix.h"

#include <sstream>

namespace orx
{
    const Matrix Matrix::IDENTITY = Matrix::identity();

    Matrix::Matrix()
    {
        m_matrix = XMMATRIX(1.f, 0.f, 0.f, 0.f,
                            0.f, 1.f, 0.f, 0.f,
                            0.f, 0.f, 1.f, 0.f,
                            0.f, 0.f, 0.f, 1.f);
    }

    Matrix::Matrix(const Matrix& other)
    {
        m_matrix = XMMATRIX(&other.getFloat4x4().m[0][0]);
    }

    Matrix::Matrix(f32 m11, f32 m12, f32 m13, f32 m14,
                   f32 m21, f32 m22, f32 m23, f32 m24,
                   f32 m31, f32 m32, f32 m33, f32 m34,
                   f32 m41, f32 m42, f32 m43, f32 m44)
    {
        m_matrix = XMMATRIX(m11, m12, m13, m14,
                            m21, m22, m23, m24,
                            m31, m32, m33, m34,
                            m41, m42, m43, m44);
    }

    Matrix::Matrix(const XMMATRIX& xmmatrix)
    {
        m_matrix = xmmatrix;
    }

    Matrix& Matrix::operator=(const Matrix& rhs)
    {
        m_matrix = rhs.getXMMatrix();
        return *this;
    }

    Matrix& Matrix::operator+=(const Matrix& rhs)
    {
        m_matrix += rhs.getXMMatrix();
        return *this;
    }

    Matrix& Matrix::operator-=(const Matrix& rhs)
    {
        m_matrix -= rhs.getXMMatrix();
        return *this;
    }

    Matrix& Matrix::operator*=(const Matrix& rhs)
    {
        m_matrix *= rhs.getXMMatrix();
        return *this;
    }

    Matrix& Matrix::operator*=(const f32& rhs)
    {
        for (int i = 0; i < 4; ++i)
        {
            m_matrix.r[i] *= rhs;
        }
        return *this;
    }

    Matrix& Matrix::operator/=(const f32& rhs)
    {
        for (int i = 0; i < 4; ++i)
        {
            m_matrix.r[i] /= rhs;
        }
        return *this;
    }

    bool Matrix::operator==(const Matrix& rhs) const
    {
        for (int i = 0; i < 4; ++i)
        {
            if (!XMVector4Equal(m_matrix.r[i], rhs.getXMMatrix().r[i]))
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

    void Matrix::decompose(Vector& translation, Quaternion& rotation, Vector& scale)
    {
        XMVECTOR xmScale;
        XMVECTOR xmRotation;
        XMVECTOR xmTranslation;

        XMMatrixDecompose(&xmScale, &xmRotation, &xmTranslation, m_matrix);

        scale = Vector(xmScale);
        rotation = Quaternion(xmRotation);
        translation = Vector(xmTranslation);
    }

    f32 Matrix::determinant()
    {
        XMVECTOR determinantVector = XMMatrixDeterminant(m_matrix);
        return XMVectorGetByIndex(determinantVector, 0);
    }

    Matrix Matrix::negate(const Matrix& matrix)
    {
        return Matrix(matrix * -1.f);
    }

    Matrix Matrix::transpose(const Matrix& matrix)
    {
        return Matrix(XMMatrixTranspose(matrix.getXMMatrix()));
    }

    Matrix Matrix::fromRotateAxisAngle(const Vector& axis, const f32 angle)
    {
        return Matrix(XMMatrixRotationAxis(axis.getXMVector(), angle));
    }

    Matrix Matrix::fromRotateX(const f32 angle)
    {
        return Matrix(XMMatrixRotationX(angle));
    }

    Matrix Matrix::fromRotateY(const f32 angle)
    {
        return Matrix(XMMatrixRotationY(angle));
    }
    
    Matrix Matrix::fromRotateZ(const f32 angle)
    {
        return Matrix(XMMatrixRotationZ(angle));
    }
    
    Matrix Matrix::fromQuaternion(const Quaternion& quaternion)
    {
        return Matrix(XMMatrixRotationQuaternion(quaternion.getXMVector()));
    }
    
    Matrix Matrix::fromYawPitchRoll(const f32 yaw, const f32 pitch, const f32 roll)
    {
        Matrix m;
        Quaternion quaternion = Quaternion::fromYawPitchRoll(yaw, pitch, roll);
        m = Matrix::fromQuaternion(quaternion);
        return m;
    }
    
    Matrix Matrix::createLookAt(const Vector& position, const Vector& target, const Vector& up)
    {
        return Matrix(XMMatrixLookAtRH(position.getXMVector(), target.getXMVector(), up.getXMVector()));
    }
    
    Matrix Matrix::createOrthographic(const f32 width, const f32 height, const f32 nearZ, const f32 farZ)
    {
        return Matrix(XMMatrixOrthographicRH(width, height, nearZ, farZ));
    }
    
    Matrix Matrix::createPerspective(const f32 fov, const f32 aspect, const f32 nearZ, const f32 farZ)
    {
        return Matrix(XMMatrixPerspectiveFovRH(fov, aspect, nearZ, farZ));
    }
    
    Matrix Matrix::fromScale(const Vector& scale)
    {
        return Matrix(XMMatrixScalingFromVector(scale.getXMVector()));
    }
    
    Matrix Matrix::fromScale(const f32 scale)
    {
        return Matrix(XMMatrixScaling(scale, scale, scale));
    }
    
    Matrix Matrix::fromTranslation(const Vector& position)
    {
        return Matrix(XMMatrixTranslationFromVector(position.getXMVector()));
    }
    
    Matrix Matrix::fromTranslation(const f32 x, const f32 y, const f32 z)
    {
        return Matrix(XMMatrixTranslation(x, y, z));
    }
    
    Matrix Matrix::invert(const Matrix& matrix)
    {
        XMVECTOR detVec = XMMatrixDeterminant(matrix.getXMMatrix());
        return Matrix(XMMatrixInverse(&detVec, matrix.getXMMatrix()));
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

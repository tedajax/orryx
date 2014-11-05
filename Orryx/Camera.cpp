#include "Camera.h"

#include <iostream>

namespace orx
{
    // TODO these should be smarter
    Camera::Camera()
        : m_fov(75.f),
        m_aspect(4.f / 3.f),
        m_near(0.1f),
        m_far(1000.f),
        m_type(CAMERA_PERSPECTIVE)
    {

    }

    Camera::~Camera()
    {

    }

    void Camera::move(const Vector& amount)
    {
        m_position += amount;
    }

    void Camera::lookAt(const Vector& target)
    {
        m_rotation = Quaternion::fromLookAt(m_position, target);
    }

    void Camera::rotateAxisAngle(const Vector& axis, f32 angle)
    {
        Quaternion rotation = Quaternion::fromAxisAngle(axis, angle);
        m_rotation *= rotation;
    }

    Matrix Camera::getView() const
    {
        Vector target = Vector::transform(Vector::FORWARD, m_rotation);
        Vector up = Vector::transform(Vector::UP, m_rotation);
        Matrix m = Matrix::createLookAt(m_position, target, up);
        return m;
    }

    Matrix Camera::getProjection() const
    {
        switch (m_type)
        {
        case CAMERA_ORTHOGRAPHIC:
            return getOrthographic();

        default:
        case CAMERA_PERSPECTIVE:
            return getPerspective();
        }
    }

    Matrix Camera::getOrthographic() const
    {
        return Matrix::createOrthographic(2.f, 2.f, m_near, m_far);
    }

    Matrix Camera::getPerspective() const 
    {
        return Matrix::createPerspective(orx::radians(m_fov), m_aspect, m_near, m_far);
    }
}
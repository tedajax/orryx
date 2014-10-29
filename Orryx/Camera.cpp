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

    void Camera::move(const Vector3& amount)
    {
        m_position += amount;
    }

    void Camera::lookAt(const Vector3& target)
    {
        m_rotation = Quaternion::fromLookAt(m_position, target);
    }

    void Camera::rotateAxisAngle(const Vector3& axis, f32 angle)
    {
        Quaternion rotation = Quaternion::fromAxisAngle(axis, angle);
        m_rotation *= rotation;
    }

    Matrix Camera::getView()
    {
        Vector3 target = Vector3::transform(Vector3::FORWARD, m_rotation);
        std::cout << Vector3::FORWARD.toString() << " " << target.toString() << std::endl;
        Vector3 up = Vector3::transform(Vector3::UP, m_rotation);
        std::cout << up.toString() << std::endl;
        Matrix m = Matrix::createLookAt(m_position, target, up);
        return m;
    }

    Matrix Camera::getProjection()
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

    Matrix Camera::getOrthographic()
    {
        return Matrix::createOrthographic(2.f, 2.f, m_near, m_far);
    }

    Matrix Camera::getPerspective()
    {
        return Matrix::createPerspective(m_fov, m_aspect, m_near, m_far);
    }
}
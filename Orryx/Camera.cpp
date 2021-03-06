#include "Camera.h"

#include "OrryxLogging.h"
#include "ConfigData.h"

#include <iostream>

namespace orx
{
    // TODO these should be smarter
    Camera::Camera()
        : m_fov(75.f),
        m_near(0.1f),
        m_far(1000.f),
        m_type(CAMERA_PERSPECTIVE)
    {
        int width = ConfigData::get("screen_width");
        int height = ConfigData::get("screen_height");
        m_aspect = (f32)width / (f32)height;
    }

    Camera::~Camera()
    {

    }

    void Camera::move(const Vector& amount)
    {
        m_position += amount;
    }

    void Camera::moveDirection(const Vector& direction, const f32 amount)
    {
        Vector forward = Vector::normalize(Vector::transform(direction, m_rotation));
        m_position += forward * amount;
    }

    void Camera::lookAt(const Vector& target)
    {
        m_rotation = Quaternion::fromLookAt(m_position, target);
        Vector euler = Quaternion::toEuler(m_rotation);
        int i = 0;
    }

    void Camera::rotateAxisAngle(const Vector& axis, f32 angle)
    {
        Quaternion rotation = Quaternion::fromAxisAngle(axis, angle);
        m_rotation *= rotation;
    }

    Matrix Camera::getView() const
    {
        Vector target = m_position + Vector::transform(Vector::cForward, m_rotation);
        Vector up = Vector::transform(Vector::cUp, m_rotation);
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
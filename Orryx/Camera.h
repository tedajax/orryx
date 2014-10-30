#ifndef ORRYX_CAMERA_H
#define ORRYX_CAMERA_H

#include "OrryxTypes.h"
#include "OrryxMath.h"

namespace orx
{
    enum CameraType
    {
        CAMERA_ORTHOGRAPHIC,
        CAMERA_PERSPECTIVE,
    };

    class Camera
    {
    public:
        Camera();
        ~Camera();

        void setPosition(const Vector3& position) { m_position = position; }
        void setPosition(f32 x, f32 y, f32 z) { setPosition(Vector3(x, y, z)); }
        void move(const Vector3& amount);
        void move(f32 x, f32 y, f32 z) { move(Vector3(x, y, z)); }

        void lookAt(const Vector3& target);
        void lookAt(f32 x, f32 y, f32 z) { lookAt(Vector3(x, y, z)); }

        void rotateAxisAngle(const Vector3& axis, f32 angle);
        void rotatePitch(f32 angle) { rotateAxisAngle(Vector3::RIGHT, angle); }
        void rotateYaw(f32 angle) { rotateAxisAngle(Vector3::UP, angle); }
        void rotateRoll(f32 angle) { rotateAxisAngle(Vector3::FORWARD, angle); }

        Matrix getView();
        Matrix getProjection();

    private:
        Matrix getOrthographic();
        Matrix getPerspective();

        f32 m_fov;
        f32 m_aspect;
        f32 m_near;
        f32 m_far;

        Vector3 m_position;
        Quaternion m_rotation;
        CameraType m_type;
    };
}

#endif
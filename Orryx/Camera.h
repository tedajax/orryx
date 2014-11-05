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

        void setPosition(const Vector& position) { m_position = position; }
        void setPosition(f32 x, f32 y, f32 z) { setPosition(Vector(x, y, z)); }
        void move(const Vector& amount);
        void move(f32 x, f32 y, f32 z) { move(Vector(x, y, z)); }

        void lookAt(const Vector& target);
        void lookAt(f32 x, f32 y, f32 z) { lookAt(Vector(x, y, z)); }

        void rotateAxisAngle(const Vector& axis, f32 angle);
        void rotatePitch(f32 angle) { rotateAxisAngle(Vector::RIGHT, angle); }
        void rotateYaw(f32 angle) { rotateAxisAngle(Vector::UP, angle); }
        void rotateRoll(f32 angle) { rotateAxisAngle(Vector::FORWARD, angle); }

        Matrix getView() const;
        Matrix getProjection() const;

        const Vector& getPosition() const { return m_position; }
        const Quaternion& getRotation() const { return m_rotation; }
        const CameraType getType() const { return m_type; }

    private:
        Matrix getOrthographic() const;
        Matrix getPerspective() const;

        f32 m_fov;
        f32 m_aspect;
        f32 m_near;
        f32 m_far;

        Vector m_position;
        Quaternion m_rotation;
        CameraType m_type;
    };
}

#endif
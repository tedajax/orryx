#ifndef ORRYX_TRANSFORM_H
#define ORRYX_TRANSFORM_H

#include "OrryxTypes.h"
#include "OrryxMath.h"
#include "OrryxLogging.h"

namespace orx
{
    class Transform
    {
    public:
        Transform()
            : m_position(0.f, 0.f, 0.f, 0.f),
            m_rotation(),
            m_scale(1.f, 1.f, 1.f, 0.f)
        { }

        Transform(const Transform& other)
        {
            m_position = other.m_position;
            m_rotation = other.m_rotation;
            m_scale = other.m_scale;
        }

        ~Transform() { }

        const Matrix getWorldMatrix() const
        {
            Matrix translation = Matrix::fromTranslation(m_position);
            Matrix rotation = Matrix::fromQuaternion(m_rotation);
            Matrix scale = Matrix::fromScale(m_scale);

            Logging::LogInfo("translation", translation.toString().c_str());
            Logging::LogInfo("rotation", rotation.toString().c_str());
            Logging::LogInfo("scale", scale.toString().c_str());

            Matrix result = scale * rotation * translation;
            Logging::LogInfo("result", result.toString().c_str());
            return result;
        }

        // TODO these probably shouldn't be public but I don't feel like building
        // a good interface for this yet.
        Vector m_position;
        Quaternion m_rotation;
        Vector m_scale;
    };
}

#endif
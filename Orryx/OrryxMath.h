#ifndef ORRYX_MATH_H
#define ORRYX_MATH_H

#include "OrryxTypes.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Matrix3.h"
#include "Matrix4.h"

#define ORX_EPSILON 1e-5f;

#include <cmath>

namespace orx
{
    inline bool isApproximatelyEqual(const f32& lhs, const f32& rhs)
    {
        return fabs(rhs - lhs) < ORX_EPSILON;
    }
}

#endif
#ifndef ORRYX_MATH_H
#define ORRYX_MATH_H

#include "OrryxTypes.h"

#include "Vector2.h"
#include "Vector3.h"
//#include "Vector4.h"

#include "Matrix.h"

#include "Quaternion.h"

#define ORX_EPSILON 1e-5f;

#include <cmath>

namespace orx
{
    inline bool isApproximatelyEqual(const f32& lhs, const f32& rhs)
    {
        return fabs(rhs - lhs) < ORX_EPSILON;
    }

    inline f32 clamp(const f32& val, const f32& min, const f32& max)
    {
        f32 v = val;
        if (v < min) { v = min; }
        else if (v > max) { v = max; }

        return val;
    }

    inline f32 lerp(const f32& start, const f32& end, const f32& t)
    {
        return start + (end - start) * t;
    }

    inline f32 sqrf(const f32& val)
    {
        return val * val;
    }
}

#endif
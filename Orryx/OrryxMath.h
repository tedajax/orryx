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
    static const f32 PI = 3.14159265f;
    static const f32 PI_OVER_2 = 1.57079633f;
    static const f32 TWO_PI = 6.28318531f;

    inline f32 radians(f32 degrees)
    {
        return degrees * (PI / 180.f);
    }

    inline f32 degrees(f32 radians)
    {
        return radians * (180.f / PI);
    }

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
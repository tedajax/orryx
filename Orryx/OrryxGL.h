#ifndef ORRYX_GL_H
#define ORRYX_GL_H

#include <GL/glew.h>

#include "OrryxTypes.h"
#include "OrryxMath.h"

#define GL_VECTOR(vector) (&(vector.getFloat4()).m[0])
#define GL_MATRIX(matrix) (&(matrix.getFloat4x4()).m[0][0])

namespace orx
{
    namespace GL
    {
        void uniform4fv(GLint uniform, Vector vec);
        void uniformMatrix4fv(GLint uniform, Matrix mat);
    }
}

#endif
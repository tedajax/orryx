#ifndef ORRYX_GL_H
#define ORRYX_GL_H

#include <GL/glew.h>

#include "OrryxTypes.h"
#include "OrryxMath.h"

namespace orx
{
    namespace GL
    {
        void uniform4fv(GLint uniform, Vector vec);
        void uniformMatrix4fv(GLint uniform, Matrix mat);
    }
}

#endif
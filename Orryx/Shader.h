#ifndef ORRYX_SHADER_H
#define ORRYX_SHADER_H

#include <GL/glew.h>

#include "OrryxTypes.h"

namespace orx
{
    class Shader
    {
    public:
        Shader();
        Shader(const char* vertFile, const char* fragFile);
        ~Shader();

        void create(const char* vertFile, const char* fragFile);
        void destroy();

        GLint getUniform(const char* name);

        void use();

    private:
        GLuint loadShader(const char* filename, GLenum shaderType);
        GLuint linkProgram();

    private:
        GLuint m_vertex;
        GLuint m_fragment;
        GLuint m_program;

        struct UniformPair
        {
            char* m_name;
            GLuint m_uniform;
        };

        enum { MAX_UNIFORMS = 20 };

        UniformPair m_uniforms[MAX_UNIFORMS];
        u32 m_uniformCount;
    };
}

#endif
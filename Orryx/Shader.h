#ifndef ORRYX_SHADER_H
#define ORRYX_SHADER_H

#include <GL/glew.h>

#include <map>

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
        GLint getUniformBlock(const char* name);

        void use();
        GLuint getProgram() { return m_program; }

    private:
        GLuint loadShader(const char* filename, GLenum shaderType);
        GLuint linkProgram();

    private:
        GLuint m_vertex;
        GLuint m_fragment;
        GLuint m_program;

        enum { MAX_UNIFORMS = 20, MAX_UNIFORM_BLOCKS = 20 };

        std::map<std::string, GLuint> m_uniforms;
        std::map<std::string, GLuint> m_uniformBlocks;
    };
}

#endif
#ifndef ORRYX_SHADER_H
#define ORRYX_SHADER_H

#include <GL/glew.h>
#include <map>

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

        GLuint getUniform(const char* name);

        void use();

    private:
        GLuint loadShader(const char* filename, GLenum shaderType);
        GLuint linkProgram();

    private:
        GLuint m_vertex;
        GLuint m_fragment;
        GLuint m_program;

        std::map<std::string, GLuint> m_uniforms;
    };
}

#endif
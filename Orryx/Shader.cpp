#include "Shader.h"

#include "OrryxFile.h"
#include "OrryxLogging.h"
#include <string>
#include <cstdio>

namespace orx
{
    Shader::Shader()
        : m_vertex(0),
        m_fragment(0),
        m_program(0)
    {

    }

    Shader::Shader(const char* vertFile, const char* fragFile)
        : Shader()
    {
        create(vertFile, fragFile);
    }

    Shader::~Shader()
    {
        destroy();
    }

    void Shader::create(const char* vertFile, const char* fragFile)
    {
        m_vertex = loadShader(vertFile, GL_VERTEX_SHADER);
        m_fragment = loadShader(fragFile, GL_FRAGMENT_SHADER);

        m_program = linkProgram();
    }

    void Shader::destroy()
    {
        glDeleteShader(m_vertex);
        glDeleteShader(m_fragment);
        glDeleteProgram(m_program);
    }

    GLint Shader::getUniform(const char* name)
    {
        return glGetUniformLocation(m_program, name);
    }

    GLint Shader::getUniformBlock(const char* name)
    {
        return glGetUniformBlockIndex(m_program, name);
    }

    void Shader::use()
    {
        glUseProgram(m_program);
    }

    GLuint Shader::loadShader(const char* filename, GLenum shaderType)
    {
        std::string shaderStr = orx::loadFileString(filename);
        if (shaderStr.length() == 0)
        {
            return 0;
        }

        const char* shader = shaderStr.c_str();

        GLuint shaderId = glCreateShader(shaderType);

        glShaderSource(shaderId, 1, &shader, nullptr);
        glCompileShader(shaderId);

        GLint compileResult = GL_FALSE;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);
        
        if (compileResult != GL_TRUE)
        {
            int logLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
            char* log = new char[logLength];
            glGetShaderInfoLog(shaderId, logLength, nullptr, log);
            fprintf(stderr, "Shader compile error: %s\n", log);
            return 0;
        }

        return shaderId;
    }

    GLuint Shader::linkProgram()
    {
        if (!m_vertex || !m_fragment)
        {
            return 0;
        }

        GLuint programId = glCreateProgram();
        glAttachShader(programId, m_vertex);
        glAttachShader(programId, m_fragment);
        glLinkProgram(programId);

        GLint linkResult = GL_FALSE;
        glGetProgramiv(programId, GL_LINK_STATUS, &linkResult);
        if (linkResult != GL_TRUE)
        {
            int logLength;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
            char* log = new char[logLength];
            glGetProgramInfoLog(programId, logLength, nullptr, log);
            fprintf(stderr, "Shader link error: %s\n", log);
        }

        return programId;
    }
}
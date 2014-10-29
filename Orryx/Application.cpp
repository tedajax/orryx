#include "Application.h"

#include "Shader.h"
#include "Camera.h"

#include <cassert>
#include <iostream>
#include <cstdio>

#include <GL/glew.h>

namespace orx
{
    Application::Application(ApplicationConfig config)
        : m_window(config.m_windowConfig),
        m_isRunning(false),
        m_isInitialized(false),
        m_appName(config.m_appName)
    {
        
    }

    Application::~Application()
    {
        if (m_isInitialized)
        {
            m_window.terminate();
            SDL_GL_DeleteContext(m_context);
        }
    }

    bool Application::initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO) > 0)
        {
            return false;
        }

        m_window.create();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

        m_context = SDL_GL_CreateContext(m_window.raw());
        if (!m_context)
        {
            fprintf(stderr, "Failed to create context: %s\n", SDL_GetError());
        }

        SDL_GL_MakeCurrent(m_window.raw(), m_context);

        glewExperimental = GL_TRUE;
        GLenum glewResult = glewInit();
        if (glewResult != GLEW_OK)
        {
            fprintf(stderr, "GL Version: %s\n", glGetString(GL_VERSION));
            fprintf(stderr, "GLEW failed to initialize: %s\n", glewGetErrorString(glewResult));
            return false;
        }

        m_isInitialized = true;
        return true;
    }

    int Application::run(int argc, char* argv[])
    {
        assert(m_isInitialized);

        m_isRunning = true;

        Camera camera;

        static const GLfloat vertices[9] = {
            -1.f, -1.f, -1.f,
            1.f, -1.f, -1.f,
            0.f, 1.f, -1.f
        };

        camera.move(0, 0, -10);
        camera.lookAt(0, 0, 0);
        Matrix projection = camera.getProjection();
        std::cout << projection.toString();
        Matrix view = camera.getView();
        std::cout << std::endl << std::endl << view.toString();
        Matrix model = Matrix::IDENTITY;
        Matrix modelViewProjection = projection * view * model;

        GLuint vertexArrayId;
        glGenVertexArrays(1, &vertexArrayId);
        glBindVertexArray(vertexArrayId);

        GLuint vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        Shader shader("basic-vert.glsl", "basic-frag.glsl");

        GLuint matrixUniform = shader.getUniform("MVP");
        glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, modelViewProjection.unpack());

        SDL_Event event;
        glClearColor(0.f, 0.f, 0.f, 1.f);
        while (m_isRunning)
        {
            while (SDL_PollEvent(&event))
            {
                handleEvent(event);
            }

            /*update();
            render();*/
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           
            shader.use();

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glVertexAttribPointer(0,
                                  3,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  0,
                                  (void *)0);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            glDisableVertexAttribArray(0);

            SDL_GL_SwapWindow(m_window.raw());
        }

        return 0;
    }

    void Application::handleEvent(SDL_Event event)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_isRunning = false;
            break;

        case SDL_KEYDOWN:
            handleKeyDown(event.key);
            break;

        case SDL_KEYUP:
            handleKeyUp(event.key);
            break;
        }
    }

    void Application::handleKeyDown(SDL_KeyboardEvent event)
    {
        if (event.keysym.sym == SDLK_ESCAPE)
        {
            m_isRunning = false;
        }
    }

    void Application::handleKeyUp(SDL_KeyboardEvent event)
    {

    }

    void Application::update()
    {

    }

    void Application::render()
    {
        
    }
}
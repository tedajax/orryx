#include "Application.h"

#include "Shader.h"
#include "Camera.h"

#include "OrryxLogging.h"

#include <cassert>
#include <iostream>
#include <cstdio>

#include <GL/glew.h>

#include <DirectXMath.h>

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
        Logging::LogInfo("Application", "Initializing application.");

        Logging::LogInfo("Application", "Initializing SDL.");
        if (SDL_Init(SDL_INIT_VIDEO) > 0)
        {
            Logging::LogPanic("Application", "Failed to initialize SDL!");
            return false;
        }

        Logging::LogInfo("Application", "Initializing window.");
        m_window.create();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

        Logging::LogInfo("Application", "Initializing GL context.");
        m_context = SDL_GL_CreateContext(m_window.raw());
        if (!m_context)
        {
            Logging::LogPanicFormat("Application", "Failed to initialize GL context: %s", SDL_GetError());
            return false;
        }

        SDL_GL_MakeCurrent(m_window.raw(), m_context);

        Logging::LogInfo("Application", "Initializing GLEW.");
        glewExperimental = GL_TRUE;
        GLenum glewResult = glewInit();
        if (glewResult != GLEW_OK)
        {
            Logging::LogPanicFormat("Application", "GLEW failed to initialize: %s", glewGetErrorString(glewResult));
            Logging::LogPanicFormat("Application", "GL Version: %s", glGetString(GL_VERSION));
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
            -1.f, -1.f, 0.f,
            1.f, -1.f, 0.f,
            0.f, 1.f, 0.f
        };

        f32 angle = 0.f;
        f32 radius = 5.f;

        GLuint vertexArrayId;
        glGenVertexArrays(1, &vertexArrayId);
        glBindVertexArray(vertexArrayId);

        GLuint vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        Shader shader("basic-vert.glsl", "basic-frag.glsl");

        GLint matrixUniform = shader.getUniform("MVP");

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

            angle += 0.05f;

            camera.move(0, 0, 0.01f);
            camera.lookAt(0, 0, 0);
            Matrix projection = camera.getProjection();
            Matrix view = camera.getView();
            Matrix model = Matrix::IDENTITY;
            DirectX::XMMATRIX xProjection = DirectX::XMMatrixPerspectiveFovLH(75.f, 4.f / 3.f, 0.1f, 1000.f);
            DirectX::XMVECTOR xeye = DirectX::XMVectorSet(0.f, 0.f, -10.f, 1.f);
            DirectX::XMVECTOR xlook = DirectX::XMVectorSet(0.f, 0.f, 0.f, 1.f);
            DirectX::XMVECTOR xup = DirectX::XMVectorSet(0.f, 1.f, 0.f, 1.f);
            DirectX::XMMATRIX xView = DirectX::XMMatrixLookAtLH(xeye, xlook, xup);
            DirectX::XMMATRIX xMVP = xView * xProjection;
            Matrix modelViewProjection = model * view * projection;

            DirectX::XMFLOAT4X4 fMVP;
            DirectX::XMStoreFloat4x4(&fMVP, xMVP);

            glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, &fMVP.m[0][0]);

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
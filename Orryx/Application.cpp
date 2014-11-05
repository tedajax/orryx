#include "Application.h"

#include "Shader.h"
#include "Camera.h"

#include "OrryxLogging.h"
#include "OrryxGL.h"
#include "Mesh.h"
#include "MeshRenderer.h"

#include <cassert>
#include <iostream>
#include <cstdio>

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
        camera.move(0.f, 5.f, 5.f);
        camera.lookAt(0, 0, 0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        static const GLfloat vertices[24] = {
            -1.f,  1.f,  1.f, // 0
             1.f,  1.f,  1.f, // 1
            -1.f, -1.f,  1.f, // 2
             1.f, -1.f,  1.f, // 3
            -1.f,  1.f, -1.f, // 4
             1.f,  1.f, -1.f, // 5
            -1.f, -1.f, -1.f, // 6
             1.f, -1.f, -1.f, // 7
        };

        static const GLushort indices[36] = {
            // front
            0, 1, 2,
            2, 1, 3,

            // right
            1, 7, 3,
            7, 1, 5,

            // back
            5, 6, 7,
            6, 5, 4,

            // left
            4, 2, 6,
            2, 4, 0,

            // top
            4, 1, 0,
            1, 4, 5,

            // bottom
            3, 7, 6,
            6, 2, 3,
        };

        Mesh mesh;
        mesh.setVertices(vertices, 24);
        mesh.setIndices(indices, 36);

        f32 angle = 0.f;
        f32 radius = 5.f;
        
        Shader shader("basic-vert.glsl", "basic-frag.glsl");

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

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
            
            camera.move(0.1f, 0.f, 0.1f);
            camera.lookAt(camera.getPosition() + Vector(0.f, -5.f, -5.f));

            MeshRenderer meshRenderer;
            meshRenderer.setMesh(&mesh);
            meshRenderer.setShader(&shader);
            meshRenderer.setCamera(&camera);
            meshRenderer.perFrameSetup();
            const int width = 100;
            const int height = 100;
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    Transform transform;
                    transform.m_position = Vector((i - (width / 2)) * 2.f,
                        0.f,
                        (j - (height / 2)) * 2.f);
                    meshRenderer.perObjectSetup(transform);
                    meshRenderer.render(transform);
                }
            }
            

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
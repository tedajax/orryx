#include "Application.h"

#include "Shader.h"
#include "Camera.h"

#include "OrryxLogging.h"
#include "OrryxGL.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "ConfigData.h"

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
        SDL_GL_SetSwapInterval(0);

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

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        const f32 size = 5.f;
        const f32 halfSize = size / 2.f;
        Mesh mesh = Mesh::createCube(halfSize);

        f32 angle = 0.f;
        f32 radius = 5.f;
        
        Shader shader("basic-vert.glsl", "basic-frag.glsl");

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        SDL_Event event;
        glClearColor(0.f, 0.f, 0.f, 1.f);

        int width = 25;
        int height = 25;

        f32 time = 0.f;

        GLuint cameraMatricesUBO;
        glGenBuffers(1, &cameraMatricesUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, cameraMatricesUBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(f32)* 16 * 2, nullptr, GL_STREAM_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        GLint cameraUniformBlock = shader.getUniformBlock("CameraMatrices");
        GLint cameraMatricesBinding = 1;
        glUniformBlockBinding(shader.getProgram(), cameraUniformBlock, cameraMatricesBinding);
        glBindBufferRange(GL_UNIFORM_BUFFER, cameraMatricesBinding, cameraMatricesUBO, 0, sizeof(f32) * 16 * 2);
        
        while (m_isRunning)
        {
            while (SDL_PollEvent(&event))
            {
                handleEvent(event);
            }

            if (m_input.getKeyDown(SDL_SCANCODE_ESCAPE))
            {
                m_isRunning = false;
            }

            m_time.update();

            if (m_time.secondElapsed())
            {
                Logging::LogInfoFormat("FPS", "%d", m_time.fps());
            }

            /*update();
            render();*/
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           
            shader.use();

            const f32 moveSpeed = 10.f;
            f32 scaledSpeed = moveSpeed * m_time.delta();
            
            if (m_input.getKey(SDL_SCANCODE_A))
            {
                camera.moveDirection(Vector::LEFT, scaledSpeed);
            }

            if (m_input.getKey(SDL_SCANCODE_D))
            {
                camera.moveDirection(Vector::RIGHT, scaledSpeed);
            }

            if (m_input.getKey(SDL_SCANCODE_W))
            {
                camera.moveDirection(Vector::FORWARD, scaledSpeed);
            }

            if (m_input.getKey(SDL_SCANCODE_S))
            {
                camera.moveDirection(Vector::BACKWARD, scaledSpeed);
            }

            if (m_input.getKey(SDL_SCANCODE_RIGHT))
            {
                camera.rotateAxisAngle(Vector::DOWN, orx::PI * m_time.delta());
            }

            if (m_input.getKey(SDL_SCANCODE_LEFT))
            {
                camera.rotateAxisAngle(Vector::DOWN, -orx::PI * m_time.delta());
            }

            if (m_input.getKey(SDL_SCANCODE_UP))
            {
                camera.moveDirection(Vector::UP, scaledSpeed);
            }

            if (m_input.getKey(SDL_SCANCODE_DOWN))
            {
                camera.moveDirection(Vector::DOWN, scaledSpeed);
            }

            if (m_input.getKeyDown(SDL_SCANCODE_Z))
            {
                ++width;
                ++height;
            }

            if (m_input.getKeyDown(SDL_SCANCODE_X))
            {
                --width;
                --height;
            }

            MeshRenderer meshRenderer;
            meshRenderer.setMesh(&mesh);
            meshRenderer.setShader(&shader);
            meshRenderer.setCamera(&camera);
            
            glBindBuffer(GL_UNIFORM_BUFFER, cameraMatricesUBO);
            glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(f32)* 16, &camera.getView().getFloat4x4().m[0][0]);
            glBufferSubData(GL_UNIFORM_BUFFER, sizeof(f32) * 16, sizeof(f32) * 16, &camera.getProjection().getFloat4x4().m[0][0]);

            time += m_time.delta() * 4.f;

            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    Transform transform;
                    transform.m_scale.setY(0.2f);
                    transform.m_position = Vector((i - (width / 2)) * size,
                        sinf(time - i) * 1.f * cosf(time - j),
                        (j - (height / 2)) * size);
                    transform.m_rotation = Quaternion::fromAxisAngle(Vector::RIGHT, sinf(time - i * 0.1f) * orx::PI);
                    meshRenderer.perObjectSetup(transform);
                    meshRenderer.render(transform);
                }
            }
            
            m_input.update();

            
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
        case SDL_KEYUP:
            handleKeyDown(event.key);
            break;

        case SDL_WINDOWEVENT_RESIZED:
            handleResize(event.window.data1, event.window.data2);
            break;
        }
    }

    void Application::handleKeyDown(SDL_KeyboardEvent event)
    {
        m_input.onKeyEvent(event);
    }

    void Application::handleKeyUp(SDL_KeyboardEvent event)
    {

    }

    void Application::handleResize(int w, int h)
    {
        ConfigData::set("screen_width", w);
        ConfigData::set("screen_height", h);
    }

    void Application::update()
    {

    }

    void Application::render()
    {
        
    }
}
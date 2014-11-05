#ifndef ORRYX_MESH_RENDERER_H
#define ORRYX_MESH_RENDERER_H

#include "OrryxTypes.h"
#include "OrryxMath.h"
#include "OrryxGL.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"

namespace orx
{
    class MeshRenderer
    {
    public:
        MeshRenderer();
        ~MeshRenderer();

        void setMesh(Mesh* mesh) { m_mesh = mesh; }
        void setShader(Shader* shader) { m_shader = shader; }
        void setCamera(Camera* camera) { m_camera = camera; }

        void perFrameSetup();
        void perObjectSetup(const Transform& transform);
        void render(const Transform& transform);

    private:
        Mesh* m_mesh;
        Shader* m_shader;
        Camera* m_camera;
    };
}

#endif
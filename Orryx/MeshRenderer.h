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

        void render(const Transform& transform, const Camera& camera);

    private:
        Mesh* m_mesh;
        Shader* m_shader;
    };
}

#endif
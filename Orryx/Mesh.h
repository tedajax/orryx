#ifndef ORRYX_MESH_H
#define ORRYX_MESH_H

#include "OrryxTypes.h"
#include "OrryxMath.h"

#include <GL/glew.h>

#include "Shader.h"

#include <vector>

namespace orx
{
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        void setVertices(const f32* vertices, u32 count);
        void setVertices(const std::vector<Vector3>& vertices);
        void setIndices(const u16* indices, u32 count);
        void setIndices(const std::vector<u16>& indices);

        void bindVertexBuffer();
        void bindIndexBuffer();
        void enableAttribArrays();
        void disableAttribArrays();

        std::vector<Vector3> getVertices() { return m_vertices; }
        std::vector<u16> getIndicies() { return m_indices; }

        static Mesh createCube(f32 halfSize = 0.5f);

    private:
        std::vector<Vector3> m_vertices;
        std::vector<u16> m_indices;

        GLuint m_vertexPositionArray;
        GLuint m_vertexBuffer;
        GLuint m_indexBuffer;
    };
}

#endif
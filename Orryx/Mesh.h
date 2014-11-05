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
        void setIndices(const u16* indices, u32 count);
        void bindVertexBuffer();
        void bindIndexBuffer();
        void enableAttribArrays();
        void disableAttribArrays();

        std::vector<f32> getVertices() { return m_vertices; }
        std::vector<u16> getIndicies() { return m_indices; }

    private:
        std::vector<f32> m_vertices;
        std::vector<u16> m_indices;

        GLuint m_vertexPositionArray;
        GLuint m_vertexBuffer;
        GLuint m_indexBuffer;
    };
}

#endif
#include "Mesh.h"

namespace orx
{
    Mesh::Mesh()
        : m_vertexBuffer(0),
        m_indexBuffer(0),
        m_vertexPositionArray(0)
    {

    }

    Mesh::~Mesh()
    {

    }

    void Mesh::setVertices(const f32* vertices, u32 count)
    {
        if (m_vertexPositionArray)
        {
            glDeleteVertexArrays(1, &m_vertexPositionArray);
        }

        if (m_vertexBuffer)
        {
            glDeleteBuffers(1, &m_vertexBuffer);
        }

        m_vertices.clear();
        for (u32 i = 0; i < count; i += 3)
        {
            f32 x = vertices[i + 0];
            f32 y = vertices[i + 1];
            f32 z = vertices[i + 2];
            m_vertices.push_back({ x, y, z });
        }

        glGenVertexArrays(1, &m_vertexPositionArray);
        glBindVertexArray(m_vertexPositionArray);

        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vector3), &m_vertices[0], GL_STATIC_DRAW);
    }

    void Mesh::setVertices(const std::vector<Vector3>& vertices)
    {
        if (m_vertexPositionArray)
        {
            glDeleteVertexArrays(1, &m_vertexPositionArray);
        }

        if (m_vertexBuffer)
        {
            glDeleteBuffers(1, &m_vertexBuffer);
        }

        m_vertices = vertices;

        glGenVertexArrays(1, &m_vertexPositionArray);
        glBindVertexArray(m_vertexPositionArray);

        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vector3), &m_vertices[0], GL_STATIC_DRAW);
    }

    void Mesh::setIndices(const u16* indices, u32 count)
    {
        if (m_indexBuffer)
        {
            glDeleteBuffers(1, &m_indexBuffer);
        }

        m_indices.clear();
        for (u32 i = 0; i < count; ++i)
        {
            m_indices.push_back(indices[i]);
        }

        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(u16), &m_indices[0], GL_STATIC_DRAW);
    }

    void Mesh::setIndices(const std::vector<u16>& indices)
    {
        if (m_indexBuffer)
        {
            glDeleteBuffers(1, &m_indexBuffer);
        }

        m_indices = indices;

        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(u16), &m_indices[0], GL_STATIC_DRAW);
    }

    void Mesh::bindVertexBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    }

    void Mesh::bindIndexBuffer()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    }

    void Mesh::enableAttribArrays()
    {
        glEnableVertexAttribArray(0);
    }

    void Mesh::disableAttribArrays()
    {
        glDisableVertexAttribArray(0);
    }

    Mesh Mesh::createCube(f32 halfSize /* = 0.5f */)
    {
        static const GLfloat vertices[24] = {
            -halfSize, halfSize, halfSize, // 0
            halfSize, halfSize, halfSize, // 1
            -halfSize, -halfSize, halfSize, // 2
            halfSize, -halfSize, halfSize, // 3
            -halfSize, halfSize, -halfSize, // 4
            halfSize, halfSize, -halfSize, // 5
            -halfSize, -halfSize, -halfSize, // 6
            halfSize, -halfSize, -halfSize, // 7
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

        return mesh;
    }
}
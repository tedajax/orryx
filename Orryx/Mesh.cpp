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
}
#include "Mesh.h"

namespace orx
{
    Mesh::Mesh()
        : m_vertexBuffer(0),
        m_normalBuffer(0),
        m_indexBuffer(0),        
        m_vertexPositionArray(0),
        m_vertexNormalArray(0)
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

    void Mesh::setNormals(const f32* normals, u32 count)
    {
        if (m_vertexNormalArray)
        {
            glDeleteVertexArrays(1, &m_vertexNormalArray);
        }

        if (m_normalBuffer)
        {
            glDeleteBuffers(1, &m_normalBuffer);
        }

        m_normals.clear();
        for (u32 i = 0; i < count; i += 3)
        {
            f32 x = normals[i + 0];
            f32 y = normals[i + 1];
            f32 z = normals[i + 2];
            m_vertices.push_back({ x, y, z });
        }

        glGenVertexArrays(1, &m_vertexNormalArray);
        glBindVertexArray(m_vertexNormalArray);

        glGenBuffers(1, &m_normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vector3), &m_vertices[0], GL_STATIC_DRAW);
    }

    void Mesh::setNormals(const std::vector<Vector3>& normals)
    {
        if (m_vertexNormalArray)
        {
            glDeleteVertexArrays(1, &m_vertexNormalArray);
        }

        if (m_normalBuffer)
        {
            glDeleteBuffers(1, &m_normalBuffer);
        }

        m_normals = normals;

        glGenVertexArrays(1, &m_vertexNormalArray);
        glBindVertexArray(m_vertexNormalArray);

        glGenBuffers(1, &m_normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
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

    void Mesh::calculateNormals()
    {
        std::vector<Vector3> normals;

        for (int i = 0; i < m_indices.size() / 3; ++i)
        {
            u16 i1 = m_indices[i * 3 + 0];
            u16 i2 = m_indices[i * 3 + 1];
            u16 i3 = m_indices[i * 3 + 2];

            Vector3 v1 = m_vertices[i2];
            Vector3 v2 = m_vertices[i1];

            Vector normal = Vector::normalize(Vector::cross(Vector(v1), Vector(v2)));

            Vector3 normalV3 = {
                normal.getX(),
                normal.getY(),
                normal.getZ()
            };

            normals.push_back(normalV3);
        }

        setNormals(normals);
    }

    void Mesh::bindVertexBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    }

    void Mesh::bindNormalBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
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
        mesh.calculateNormals();

        return mesh;
    }
}
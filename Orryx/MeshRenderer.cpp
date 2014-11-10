#include "MeshRenderer.h"
#include "OrryxLogging.h"

namespace orx
{
    MeshRenderer::MeshRenderer() { }
    MeshRenderer::~MeshRenderer() { }

    void MeshRenderer::perFrameSetup()
    {
        assert(m_mesh && m_shader && m_camera);

        m_shader->use();

        Matrix projection = m_camera->getProjection();
        Matrix view = m_camera->getView();

        

        GL::uniformMatrix4fv(m_shader->getUniform("view"), view);
        GL::uniformMatrix4fv(m_shader->getUniform("projection"), projection);
    }

    void MeshRenderer::perObjectSetup(const Transform& transform)
    {
        Matrix world = transform.getWorldMatrix();

        GL::uniformMatrix4fv(m_shader->getUniform("model"), world);
    }

    void MeshRenderer::render(const Transform& transform)
    {
        glEnableVertexAttribArray(0);
        m_mesh->bindVertexBuffer();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        m_mesh->bindNormalBuffer();
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        m_mesh->bindIndexBuffer();
        glDrawElements(GL_TRIANGLES, (GLsizei)m_mesh->getIndicies().size(), GL_UNSIGNED_SHORT, nullptr);
        
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);        
    }
}
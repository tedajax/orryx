#include "MeshRenderer.h"
#include "OrryxLogging.h"

namespace orx
{
    MeshRenderer::MeshRenderer() { }
    MeshRenderer::~MeshRenderer() { }

    void MeshRenderer::render(const Transform& transform, const Camera& camera)
    {
        assert(m_mesh && m_shader);

        m_shader->use();

        Matrix projection = camera.getProjection();
        Matrix view = camera.getView();
        Matrix world = Matrix::IDENTITY;  //transform.getWorldMatrix();

        DirectX::XMFLOAT4X4 fWorld;
        XMStoreFloat4x4(&fWorld, world.getXMMatrix());

        GL::uniformMatrix4fv(m_shader->getUniform("model"), world);
        GL::uniformMatrix4fv(m_shader->getUniform("view"), view);
        GL::uniformMatrix4fv(m_shader->getUniform("projection"), projection);

        m_mesh->bindVertexBuffer();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        m_mesh->bindIndexBuffer();
        glDrawElements(GL_TRIANGLES, (GLsizei)m_mesh->getIndicies().size(), GL_UNSIGNED_SHORT, &m_mesh->getIndicies()[0]);

        glDisableVertexAttribArray(0);
    }
}
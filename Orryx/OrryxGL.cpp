#include "OrryxGL.h"

namespace orx
{
    namespace GL
    {
        void uniform4fv(GLint uniform, Vector vec)
        {
            DirectX::XMFLOAT4 fVec;
            XMStoreFloat4(&fVec, vec.getXMVector());
            glUniform4fv(uniform, 1, &fVec.x);
        }

        void uniformMatrix4fv(GLint uniform, Matrix mat)
        {
            DirectX::XMFLOAT4X4 fMat;
            XMStoreFloat4x4(&fMat, mat.getXMMatrix());
            glUniformMatrix4fv(uniform, 1, GL_FALSE, &fMat.m[0][0]);
        }
    }
}
#pragma once
#include "Renderer/VertexArray.h"

namespace GreyboxEngine
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

       //const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
       //std::shared_ptr<IndexBuffer> GetIndexBuffer() const override;

        
        
    private:
        unsigned int m_vao;
    };
}

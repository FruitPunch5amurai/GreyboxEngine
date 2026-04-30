#pragma once
#include "Renderer/Buffer.h"

namespace GreyboxEngine
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer();
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;
		
        virtual void SetData(const void* data, uint32_t size) override;

        float* GetVertices() const override {return m_vertices;}
    
    private:
        unsigned int m_vbo;
        float* m_vertices;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;

    private:
        unsigned int m_ibo;
    };

}

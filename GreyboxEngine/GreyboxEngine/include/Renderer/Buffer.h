#pragma once
namespace GreyboxEngine
{

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(const void* data, uint32_t size) = 0;

        virtual float* GetVertices() const = 0;

        // Creation
        static std::shared_ptr<VertexBuffer> Create();
        static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
    };

    // Currently only supports 32-bit index buffers
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        // Creation
        static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    };
}

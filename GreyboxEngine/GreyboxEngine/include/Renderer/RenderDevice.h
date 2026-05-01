#pragma once
#include "Buffer.h"
#include <memory>

#include "VertexLayout.h"

namespace GreyboxEngine
{
    class RenderDevice
    {
    public:
        virtual ~RenderDevice() = default;

        // === Buffers ===
        virtual VertexArrayHandle CreateVertexArray() = 0;
        virtual VertexBufferHandle CreateVertexBuffer() = 0;
        virtual VertexBufferHandle CreateVertexBuffer(void* data, uint32_t size) = 0;
        virtual IndexBufferHandle CreateIndexBuffer(uint32_t* indices, uint32_t count) = 0;
        virtual void BindVertexArray(VertexArrayHandle handle) = 0;
        virtual void BindVertexBuffer(VertexBufferHandle handle) = 0;
        virtual void BindIndexBuffer(IndexBufferHandle handle) = 0;
        virtual void UnbindVertexArray(VertexArrayHandle handle) = 0;
        virtual void UnbindVertexBuffer(VertexBufferHandle handle) = 0;
        virtual void UnbindIndexBuffer(IndexBufferHandle handle) = 0;
        virtual void SetVertexBufferData(VertexBufferHandle handle, const void* data, uint32_t size) = 0;
        virtual void PassVertexLayout(const VertexLayout& layout) = 0;
        
        // === Shaders ===
        virtual ShaderProgramHandle CreateShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) = 0;
        virtual ShaderProgramHandle CreateShaderFromFile(const std::string& name, const std::string& vertexSrcFilename, const std::string& fragmentSrcFilename) = 0;

        virtual void BindShader(ShaderProgramHandle handle) = 0;
        virtual void UnbindShader(ShaderProgramHandle handle) = 0;

        // === Drawing ===
        virtual void Draw(VertexArrayHandle vaoHandle, uint32_t vertexCount) = 0;
        static std::unique_ptr<RenderDevice> Create();
    };
}

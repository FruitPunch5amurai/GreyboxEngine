#pragma once
#include "Renderer/RenderDevice.h"

namespace GreyboxEngine
{
    class OpenGLRenderDevice : public RenderDevice
    {
        struct GLVertexArrayInternal
        {
            uint32_t vaoId = 0;
        };

        struct GLVertexBufferInternal
        {
            uint32_t vboId = 0;
            uint32_t size = 0;
        };

        struct GLIndexBufferInternal
        {
            uint32_t iboId = 0;
            uint32_t size = 0;
        };

        struct GLShaderProgramInternal
        {
            uint32_t shaderProgram = 0;
            std::string name;
        };

    public :
        OpenGLRenderDevice();
        virtual ~OpenGLRenderDevice();
        VertexArrayHandle CreateVertexArray() override;
        VertexBufferHandle CreateVertexBuffer() override;
        VertexBufferHandle CreateVertexBuffer(void* data, uint32_t size) override;
        IndexBufferHandle CreateIndexBuffer(uint32_t* indices, uint32_t count) override;
        void BindVertexArray(VertexArrayHandle handle) override;
        void BindVertexBuffer(VertexBufferHandle handle) override;
        void BindIndexBuffer(IndexBufferHandle handle) override;
        void UnbindVertexArray(VertexArrayHandle handle) override;
        void UnbindVertexBuffer(VertexBufferHandle handle) override;
        void UnbindIndexBuffer(IndexBufferHandle handle) override;
        void SetVertexBufferData(VertexBufferHandle handle, const void* data, uint32_t size) override;
        void PassVertexLayout(const VertexLayout& layout) override;

        // === Shaders ===
        ShaderProgramHandle CreateShader(const std::string& name, const std::string& vertexSrc,
                                         const std::string& fragmentSrc) override;
        ShaderProgramHandle CreateShaderFromFile(const std::string& name, const std::string& vertexSrcFilename,
                                                         const std::string& fragmentSrcFilename) override;

        void BindShader(ShaderProgramHandle handle) override;
        void UnbindShader(ShaderProgramHandle handle) override;

        // === Drawing ===
        void Draw(VertexArrayHandle vaoHandle, uint32_t vertexCount) override;

    private:
        std::vector<GLVertexArrayInternal> m_vaos;
        std::vector<GLVertexBufferInternal> m_vbos;
        std::vector<GLIndexBufferInternal> m_ibos;
        std::vector<GLShaderProgramInternal> m_shaderPrograms;
    };
}

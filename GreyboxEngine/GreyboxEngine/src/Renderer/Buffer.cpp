#include "gbepch.h"
#include "Renderer/Buffer.h"

#include "Core.h"
#include "Logging/Logging.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GreyboxEngine
{
    // VertexBuffer
    std::shared_ptr<VertexBuffer> VertexBuffer::Create()
    {
#ifdef GBE_RENDER_API_OPENGL
        return std::make_shared<OpenGLVertexBuffer>();
#endif
        GBE_LOG_ERROR("Failed to create VertexBuffer!");
        return nullptr;
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
#ifdef GBE_RENDER_API_OPENGL
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
#endif
        GBE_LOG_ERROR("Failed to create VertexBuffer!");
        return nullptr;
    }

    // Index Buffer
    std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
#ifdef GBE_RENDER_API_OPENGL
        return std::make_shared<OpenGLIndexBuffer>(indices, count);
#endif
        GBE_LOG_ERROR("Failed to create IndexBuffer!");
        return nullptr;
    }
}

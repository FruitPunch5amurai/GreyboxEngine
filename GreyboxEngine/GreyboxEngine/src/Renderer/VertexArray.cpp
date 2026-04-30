#include "gbepch.h"
#include "Core.h"
#include "Renderer/VertexArray.h"

#include "Logging/Logging.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GreyboxEngine
{
    std::shared_ptr<VertexArray> VertexArray::Create()
    {
#ifdef GBE_RENDER_API_OPENGL
        return std::make_shared<OpenGLVertexArray>();
#endif
        GBE_LOG_ERROR("Failed to create VertexArray!");
        return nullptr;
    }
}

#include "gbepch.h"
#include "Renderer/RenderDevice.h"
#include "Core.h"

#ifdef GBE_RENDER_API_OPENGL
#include "Platform/OpenGL/OpenGLRenderDevice.h"
#endif

namespace GreyboxEngine
{
    std::unique_ptr<RenderDevice> RenderDevice::Create()
    {
#ifdef GBE_RENDER_API_OPENGL
    return std::make_unique<OpenGLRenderDevice>();
#endif
        return nullptr;
    }
}

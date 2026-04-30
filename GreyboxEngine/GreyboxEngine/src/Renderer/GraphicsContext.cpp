#include "gbepch.h"
#include "Renderer/GraphicsContext.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Window/WindowsWindow.h"

GreyboxEngine::GraphicsContext* GreyboxEngine::GraphicsContext::Create(void* window)
{
    // Only supports OpenGL atm
#ifdef GBE_RENDER_API_OPENGL
    return new OpenGLContext(static_cast<GLFWwindow*>(window));
#endif
    return nullptr;
}

#include "gbepch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Core.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Logging/Logging.h"

namespace GreyboxEngine
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_windowHandle(windowHandle)
    {
        GBE_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        GBE_CORE_ASSERT(status, "Failed to initialize Glad!");

        auto vendor =  reinterpret_cast<const char*>(glGetString(GL_VENDOR));
        auto renderer =  reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        auto version =  reinterpret_cast<const char*> (glGetString(GL_VERSION));
        
        GBE_CORE_INFO("OpenGL Info:");
        GBE_CORE_INFO("  Company: {0}", vendor);
        GBE_CORE_INFO("  GPU: {0}",renderer);
        GBE_CORE_INFO("  Version: {0}", version);

        GBE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5),
                        "Greybox requires at least OpenGL version 4.5!");
    }

    void OpenGLContext::SwapBuffers()
    {
        // This function is OpenGL Specific, which is why it goes here
        glfwSwapBuffers(m_windowHandle);
    }
}

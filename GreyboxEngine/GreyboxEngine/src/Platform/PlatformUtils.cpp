#include "gbepch.h"
#include "Platform/PlatformUtils.h"

#include <GLFW/glfw3.h>

namespace GreyboxEngine
{
    float Time::GetTime()
    {
        return static_cast<float>(glfwGetTime());
    }
}

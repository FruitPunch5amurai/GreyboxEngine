#include "gbepch.h"
#include "Platform/PlatformUtils.h"

#ifdef GBE_WINDOW_API_GLFW
#include <GLFW/glfw3.h>
#endif

namespace GreyboxEngine
{
    float Time::GetTime()
    {
#ifdef GBE_WINDOW_API_GLFW
    return glfwGetTime();
#endif
        return 0;
    }
}

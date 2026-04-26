#include "gbepch.h"
#include "Input/Input.h"

#include "Application/Application.h"

#ifdef GBE_WINDOW_API_GLFW
#include <GLFW/glfw3.h>
#endif

namespace GreyboxEngine
{
    bool Input::IsKeyPressed(int keycode)
    {
#ifdef GBE_WINDOW_API_GLFW
        auto* window = static_cast<GLFWwindow*>(GreyboxEngine::Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
#else
        return false;
#endif
    }

    bool Input::IsMouseButtonPressed(unsigned keycode)
    {
#ifdef GBE_WINDOW_API_GLFW
        auto* window = static_cast<GLFWwindow*>(GreyboxEngine::Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetMouseButton(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
#else
        return false;
#endif
    }
}

#include "gbepch.h"
#include "Input/Input.h"

#include "Application/Application.h"

#include <GLFW/glfw3.h>

namespace GreyboxEngine
{
    bool Input::IsKeyPressed(int keycode)
    {
        auto* window = static_cast<GLFWwindow*>(GreyboxEngine::Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(unsigned keycode)
    {
        auto* window = static_cast<GLFWwindow*>(GreyboxEngine::Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetMouseButton(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
}

#include "gbepch.h"
#include "Input/Input.h"

#include "Application/Application.h"

#ifdef GBE_WINDOW_API_GLFW
#include <GLFW/glfw3.h>
#endif

namespace GreyboxEngine
{
    bool Input::IsKeyPressed(unsigned int keycode)
    {
#ifdef GBE_WINDOW_API_GLFW
        auto* window = static_cast<GLFWwindow*>(GreyboxEngine::Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
#else
        return false;
#endif
    }

    bool Input::IsKeyReleased(unsigned keycode)
    {
#ifdef GBE_WINDOW_API_GLFW
        auto* window = static_cast<GLFWwindow*>(GreyboxEngine::Application::Get().GetWindow().GetNativeWindow());
        //if (Application::Get().keyWasPressed[keycode] && glfwGetKey(window, keycode) == GLFW_RELEASE)
        //{
        //    return true;
        //}
        return false;
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

    bool Input::IsMouseButtonReleased(unsigned keycode)
    {
#ifdef GBE_WINDOW_API_GLFW
        auto* window = static_cast<GLFWwindow*>(GreyboxEngine::Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetMouseButton(window, keycode);
        return state == GLFW_RELEASE;
#else
            return false;
#endif
    }
}

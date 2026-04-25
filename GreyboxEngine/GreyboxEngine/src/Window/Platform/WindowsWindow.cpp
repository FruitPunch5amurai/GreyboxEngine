#include "gbepch.h"
#include "Window/Platform/WindowsWindow.h"
#include "Logging/Logging.h"
#include "Window/KeyCodes.h"
#include "Window/Events/ApplicationEvent.h"
#include "Window/Events/Event.h"
#include "Window/Events/KeyEvent.h"
#include "Window/Events/MouseEvent.h"
#include <glad/glad.h>

namespace GreyboxEngine
{
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        m_data.Title = props.Title;
        m_data.Width = props.Width;
        m_data.Height = props.Height;

        GBE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            GBE_CORE_ASSERT(success, "Could not initialize GLFW")

            s_GLFWInitialized = true;
        }

        // Hints
        const char* glsl_version = "#version 410";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac

        m_window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), props.Title.c_str(),
                                    nullptr, nullptr);

        glfwMakeContextCurrent(m_window);

        // GLAD Stuff
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        GBE_CORE_ASSERT(status, "Failed to initialize Glad");
        
        glfwSetWindowUserPointer(m_window, &m_data);
        SetVSync(true);
        
        //GLFW Events
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, const int width, const int height)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch (action)
            {
            case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
            case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            default: break;
            }
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
        {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch (action)
            {
            case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            default: break;
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event((float)xOffset, (float) yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, const double xPos, const double yPos)
        {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

        glfwSetErrorCallback([](int error_code, const char* description)
        {
            GBE_CORE_ERROR("GLFW Error {0}: {1}", error_code, description);
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int c)
        {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            KeyTypedEvent event(c);
            data.EventCallback(event);
        });
        
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void WindowsWindow::SetVSync(const bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_data.VSync;
    }
}

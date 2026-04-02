#include "gbepch.h"
#include "Window/Platform/WindowsWindow.h"
#include "Logging/Logging.h"

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

        m_window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), props.Title.c_str(), nullptr, nullptr);
        
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);
        SetVSync(true);
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

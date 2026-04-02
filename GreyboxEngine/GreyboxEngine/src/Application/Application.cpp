#include "gbepch.h"
#include "Application/Application.h"

#include <cstdio>

#include "Logging/Logging.h"
#include "Window/Window.h"
#include "Window/Events/ApplicationEvent.h"
#include "Window/Events/Event.h"

namespace GreyboxEngine
{
    Application::Application()
    {
        GreyboxEngine::Logging::Init();
        
        m_window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(m_running)
        {
            m_window->OnUpdate();
        }
    }
}

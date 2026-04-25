#include "gbepch.h"
#include "Application/Application.h"

#include <cstdio>

#include "GLFW/glfw3.h"
#include "Input/Input.h"
#include "Logging/Logging.h"
#include "Platform/PlatformUtils.h"
#include "Window/Window.h"
#include "Window/Events/ApplicationEvent.h"
#include "Window/Events/Event.h"
#include "Window/Events/MouseEvent.h"
#include "Input/KeyCode.h"

namespace GreyboxEngine
{

    Application* Application::s_instance = nullptr;
    
    Application::Application()
    {
        GreyboxEngine::Logging::Init();
        s_instance = this;
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(GBE_BIND_EVENT_FN(&Application::OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_layerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::PopLayer(Layer* layer)
    {
        m_layerStack.PopLayer(layer);
        layer->OnDetach();
    }

    void Application::PopOverlay(Layer* layer)
    {
        m_layerStack.PopOverlay(layer);
        layer->OnDetach();
    }

    void Application::OnEvent(Event& e)
    {
        m_eventDispatcher.Dispatch<WindowCloseEvent>(e,GBE_BIND_EVENT_FN(&Application::OnWindowCloseEvent));
        
        GBE_CORE_INFO("{0}", e.ToString());

       for(auto it = m_layerStack.end(); it != m_layerStack.begin();)
       {
           (*--it)->OnEvent(e);
           if (e.Handled)
               break;
       }
    }

    bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
    {
        m_running = false;
        return true;
    }
    
    void Application::Run()
    {
        while(m_running)
        {
            const float time = Time::GetTime();
            
            for (Layer* layer : m_layerStack)
            {
                layer->OnUpdate(time);
            }
            
            m_window->OnUpdate();
            
        }
    }


}

#include "gbepch.h"
#include "Application/Application.h"

#include <cstdio>

#include "Logging/Logging.h"
#include "Window/Events/ApplicationEvent.h"
#include "Window/Events/Event.h"

namespace GreyboxEngine
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        /*
         *  Initialization
         */
        
        GreyboxEngine::Logging::Init();
        GBE_INFO("Logging Initialized...");
        GBE_LOG_INFO("Logging Initialized...");

        WindowResizeEvent e(1280, 720);
        if (e.GetEventType() == EventType::WindowResize)
        {
            GBE_LOG_INFO(e.ToString());
        }
        
        while(true)
        {
            
        }
    }
}

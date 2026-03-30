#include "Application/Application.h"

#include <cstdio>

#include "Logging/Logging.h"

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

        while(true)
        {
            
        }
    }
}

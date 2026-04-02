#pragma once

#include "Core.h"
#include "Window/Window.h"

namespace GreyboxEngine
{
    class Window;

    class GBE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_window;
        bool m_running = true;
    };

    // To be define in client
    Application* CreateApplication();
}
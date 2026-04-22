#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Window/Layers/LayerStack.h"

namespace GreyboxEngine
{
    class WindowCloseEvent;
}

namespace GreyboxEngine
{
    class Window;

    class GBE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
        bool OnWindowCloseEvent(WindowCloseEvent& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
    private:
        std::unique_ptr<Window> m_window;
        EventDispatcher m_eventDispatcher;

        bool m_running = true;
        LayerStack m_layerStack;
    };

    // To be define in client
    Application* CreateApplication();
}

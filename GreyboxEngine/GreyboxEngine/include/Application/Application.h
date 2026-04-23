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

        inline static Application& Get(){return *s_instance;}
        inline Window& GetWindow(){return *m_window;}
    private:
        std::unique_ptr<Window> m_window;
        EventDispatcher m_eventDispatcher;
        static Application* s_instance;
        
        bool m_running = true;
        LayerStack m_layerStack;
    };

    // To be define in client
    Application* CreateApplication();
}

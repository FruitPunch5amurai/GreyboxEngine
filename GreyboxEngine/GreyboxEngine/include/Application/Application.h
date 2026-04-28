#pragma once

#include <queue>

#include "Core.h"
#include "Window/Window.h"
#include "Window/Layers/LayerStack.h"

namespace GreyboxEngine
{
    class ImGuiLayer;
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
        void OnEvent(Event e);
        bool OnWindowCloseEvent(WindowCloseEvent& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);

        void Shutdown();
        
        inline static Application& Get(){return *s_instance;}
        inline Window& GetWindow(){return *m_window;}
        
    private:
        static Application* s_instance;

        std::queue<Event> m_eventQueue;
        std::unique_ptr<Window> m_window;
        EventDispatcher m_eventDispatcher;
        LayerStack m_layerStack;
        ImGuiLayer* m_imGuiLayer;
        
        bool m_running = true;
        
        void ProcessEventQueue();
    };

    // To be define in client
    Application* CreateApplication();
}

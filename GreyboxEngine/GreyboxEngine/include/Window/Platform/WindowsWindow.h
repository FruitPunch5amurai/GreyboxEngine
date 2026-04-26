#pragma once

#include "Window/Window.h"

#include <GLFW/glfw3.h>

namespace GreyboxEngine
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        ~WindowsWindow() override;

        void Begin() override;
        void End() override;
        void OnUpdate() override;

        unsigned int GetWidth() const override {return m_data.Width; }
        unsigned int GetHeight() const override {return m_data.Height; }

        void SetEventCallback(const EventCallbackFn& callback) override {m_data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;
        void Close() override;
        bool IsClosing() override;
        void* GetNativeWindow() const override { return m_window; }

        // TESTING
    private:
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        GLFWwindow* m_window;
        WindowData m_data;

        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    };
    
}

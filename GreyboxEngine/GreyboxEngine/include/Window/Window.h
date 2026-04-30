#pragma once

#include "gbepch.h"


#include "Core.h"
#include "Events/Event.h"

namespace GreyboxEngine
{
    class GraphicsContext;

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Greybox Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
                        :Title (title), Width(width), Height(height)
        {
            
        }
    };

    // Interface to be inherited by different Platforms
    class GBE_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event)>;

        virtual ~Window() = default;

        virtual void Begin() = 0;
        virtual void End() = 0;
        
        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        // Window Attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;
        virtual void* GetNativeWindow() const = 0;
        virtual GraphicsContext* GetContext() const = 0;
        virtual void Close() = 0;
        virtual bool IsClosing() = 0;
        static Window* Create(const WindowProps& props = WindowProps());
    };
}
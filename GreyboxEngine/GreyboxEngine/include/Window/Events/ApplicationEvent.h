#pragma once

#include "Window/Events/Event.h"

namespace GreyboxEngine {

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_width(width), m_height(height) {}

        unsigned int GetWidth() const { return m_width; }
        unsigned int GetHeight() const { return m_height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_width << ", " << m_height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
    private:
        unsigned int m_width, m_height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
    };

    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick)
    };

    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate)
    };

    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender)
    };
}
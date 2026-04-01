#pragma once

#include "Core.h"

namespace GreyboxEngine
{
    // Events are currently Blocking, should change later to buffer

    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        AppTick,
        AppUpdate,
        AppRender,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; }\
                                virtual EventType GetEventType() const override {return GetStaticType(); }\
                                virtual const char* GetName() const override {return #type; }

    class GBE_API Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }
    };

    class EventDispatcher
    {
        
    public:
        EventDispatcher(Event& event): m_event(event)
        {
        }

        template <typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_event.GetEventType() == T::GetStaticType())
            {
                m_event.Handled = func(*(T*)&m_event);
                return true;
            }
            return false;
        }

    private:
        Event& m_event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}

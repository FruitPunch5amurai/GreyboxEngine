#pragma once

#include "Core.h"
#include <variant>

#include "Input/KeyCode.h"
#include "Window/MouseCodes.h"

namespace GreyboxEngine
{
    struct KeyPressedEvent
    {
        int key;
        bool isRepeat;
    };

    struct KeyReleasedEvent
    {
        int key;
    };

    struct KeyTypedEvent
    {
        unsigned int keyCode;
    };

    struct MouseScrollEvent
    {
        float x, y;
    };

    struct MouseMovedEvent
    {
        float x, y;
    };

    struct MouseButtonPressedEvent
    {
        int button;
    };

    struct MouseButtonReleasedEvent
    {
        int button;
    };

    struct WindowResizeEvent
    {
        int width, height;
    };

    struct WindowCloseEvent
    {
        /* Empty */
    };

    struct Event
    {
        // --- Common Data ---
        bool handled = false;

        // --- Unique Data ---
        std::variant<KeyPressedEvent,
                     KeyTypedEvent,
                     KeyReleasedEvent,
                     MouseScrollEvent,
                     MouseMovedEvent,
                     MouseButtonPressedEvent,
                     MouseButtonReleasedEvent,
                     WindowResizeEvent,
                     WindowCloseEvent> data;

        std::string ToString()
        {
            return std::visit([](auto&& arg) -> std::string
            {
                using T = std::decay_t<decltype(arg)>;
                std::stringstream ss;

                if constexpr (std::is_same_v<T, KeyPressedEvent>)
                    ss << "KeyPressedEvent: key=" << arg.key << " repeat=" << (arg.isRepeat ? "true" : "false");

                else if constexpr (std::is_same_v<T, KeyReleasedEvent>)
                    ss << "KeyReleasedEvent: key=" << arg.key;

                else if constexpr (std::is_same_v<T, KeyTypedEvent>)
                    ss << "KeyTypedEvent: code=" << (int)arg.keyCode;

                else if constexpr (std::is_same_v<T, MouseMovedEvent>)
                    ss << "MouseMovedEvent: x=" << arg.x << " y=" << arg.y;

                else if constexpr (std::is_same_v<T, MouseScrollEvent>)
                    ss << "MouseScrollEvent: xOffset=" << arg.x << " yOffset=" << arg.y;

                else if constexpr (std::is_same_v<T, MouseButtonPressedEvent>)
                    ss << "MouseButtonPressedEvent: button=" << (int)arg.button;

                else if constexpr (std::is_same_v<T, MouseButtonReleasedEvent>)
                    ss << "MouseButtonReleasedEvent: button=" << (int)arg.button;

                else if constexpr (std::is_same_v<T, WindowResizeEvent>)
                    ss << "WindowResizeEvent: width=" << arg.width << " height=" << arg.height;

                else if constexpr (std::is_same_v<T, WindowCloseEvent>)
                    ss << "WindowCloseEvent";

                return ss.str();
            }, data);
        }
    };


    class EventDispatcher
    {
    public:
        EventDispatcher()
        {
        }

        template <typename T, typename F>
        bool Dispatch(Event& e, const F& func)
        {
            // std::visit returns the value returned by the lambda
            return std::visit([&](auto&& arg) -> bool // Explicitly state bool return type
            {
                using VT = std::decay_t<decltype(arg)>;

                if constexpr (std::is_same_v<VT, T>)
                {
                    // arg is already the object of type T, no pointer cast needed
                    e.handled = func(arg);
                    return true;
                }

                // You MUST return a bool for every other type in the variant
                return false;
            }, e.data); // Pass the variant here
        }
    };

    // Events are currently Blocking, should change later to buffer

    /*
     
        enum class EventType
            {
                None = 0,
                WindowClose,
                WindowResize,
                WindowFocus,
                WindowLostFocus,
                WindowMoved,
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
            EventDispatcher(){}
    
            template <typename T, typename F>
            bool Dispatch(Event& e, const F& func)
            {
                if (e.GetEventType() == T::GetStaticType())
                {
                    e.Handled = func(*(T*)&e);
                    return true;
                }
                return false;
            }
        };
    
        inline std::ostream& operator<<(std::ostream& os, const Event& e)
        {
            return os << e.ToString();
        }
        */
}

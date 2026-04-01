#pragma once

#include "Window/Events/Event.h"
#include "Window/KeyCodes.h"

namespace GreyboxEngine
{
    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const {return m_keyCode; }
    
    protected:
        KeyEvent(const KeyCode keyCode) : m_keyCode(keyCode){}
        KeyCode m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const KeyCode keyCode, bool isRepeat = false) : KeyEvent(keyCode), m_isRepeat(isRepeat){}

        bool IsRepeat() const {return m_isRepeat; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (repeat = " << m_isRepeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        bool m_isRepeat;
    };
    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}


#pragma once

#include "Core.h"
#include "Window/Events/Event.h"

namespace GreyboxEngine
{
    class GBE_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach(){}
        virtual void OnDetach(){}
        virtual void OnUpdate(float time){}
        virtual void OnEvent(Event& event){}

        inline const std::string& GetName() const{ return m_debugName; }
    protected:
        std::string m_debugName;
    };
}
#pragma once

#include "Window/Layers/Layer.h"

namespace GreyboxEngine
{
    
    class GBE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnImGuiRender();
        
        void Begin();
        void End();
    private:
        float m_time = 0;
    };
}

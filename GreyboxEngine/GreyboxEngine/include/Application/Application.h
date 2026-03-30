#pragma once

#include "Core.h"

namespace GreyboxEngine
{
    class GBE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be define in client
    Application* CreateApplication();
}
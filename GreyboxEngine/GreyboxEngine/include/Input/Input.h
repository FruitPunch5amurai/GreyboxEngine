#pragma once
#include "Core.h"

namespace GreyboxEngine
{
    class GBE_API Input
    {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(unsigned int keycode);
    };
}

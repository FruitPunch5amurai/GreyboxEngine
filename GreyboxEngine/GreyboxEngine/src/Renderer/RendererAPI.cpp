#include "gbepch.h"
#include "Renderer/RendererAPI.h"

namespace GreyboxEngine
{
    template <typename T>
    std::unique_ptr<T> CreateRendererAPI()
    {
        return std::unique_ptr<T>();
    }
}
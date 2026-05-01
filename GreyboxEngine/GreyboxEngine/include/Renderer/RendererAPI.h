#pragma once
namespace GreyboxEngine
{
    template<typename T>
    class RendererAPI
    {
    public:
        void Bind(){ static_cast<T*>(this)->BindImpl();}

    protected:
        std::string m_name;
    };

    // Shader.h
    template <typename T>
    std::unique_ptr<T> CreateRendererAPI();
    
}

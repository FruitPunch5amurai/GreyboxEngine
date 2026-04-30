#pragma once


namespace GreyboxEngine
{
    template<typename T>
    class Shader
    {
    public:
        //void Bind(){ static_cast<T*>(this)->BindImpl();}

    protected:
        std::string m_name;
    };

    // Shader.h
    template <typename T>
    std::shared_ptr<T> CreateShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    
}

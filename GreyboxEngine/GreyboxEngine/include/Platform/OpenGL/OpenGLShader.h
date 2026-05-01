#pragma once
#include "Renderer/Shader.h"

namespace GreyboxEngine
{
    class OpenGLShader : public Shader<OpenGLShader>
    {
    public:
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();
        
        void Bind() const;

    private:
        unsigned int m_shaderProgram;
        
    };
}

#include "gbepch.h"
#include "Renderer/Shader.h"
#include "Core.h"
#include "Logging/Logging.h"

#ifdef GBE_RENDER_API_OPENGL
#include "Platform/OpenGL/OpenGLShader.h"
#endif

namespace GreyboxEngine
{
    template <typename T>
    std::shared_ptr<T> CreateShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        return std::make_shared<T>(name, vertexSrc, fragmentSrc);
    }

#ifdef GBE_RENDER_API_OPENGL
    // This tells the compiler: "Generate the binary code for OpenGLShader right here"
    template std::shared_ptr<OpenGLShader> CreateShader<OpenGLShader>(
        const std::string& name, 
        const std::string& vertexSrc, 
        const std::string& fragmentSrc
    );
#endif
    
}

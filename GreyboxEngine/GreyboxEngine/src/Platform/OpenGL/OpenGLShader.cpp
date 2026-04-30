#include "gbepch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "glad/glad.h"
#include "Logging/Logging.h"

namespace GreyboxEngine
{
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        m_name = name;

        // === Vertex Shader ===
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const char* cstr = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &cstr, NULL);
        glCompileShader(vertexShader);

        int  success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GBE_CORE_ERROR("Failed to compile vertex shader for {0}", name);
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        }

        // === Fragment Shader ===
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        cstr = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &cstr, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GBE_CORE_ERROR("Failed to compile fragment shader for {0}", name);
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            return;
        }

        // === Link Shaders ===
        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, vertexShader);
        glAttachShader(m_shaderProgram, fragmentShader);
        glLinkProgram(m_shaderProgram);

        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            GBE_CORE_ERROR("Failed to link fragment and vertex shader for {0}", name);
            glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
            return;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        GBE_LOG_TRACE("Shader {0} Created", m_name);

    }

    OpenGLShader::~OpenGLShader()
    {
        GBE_LOG_TRACE("Shader {0} Destroyed", m_name);
        glDeleteProgram(m_shaderProgram);
    }
}

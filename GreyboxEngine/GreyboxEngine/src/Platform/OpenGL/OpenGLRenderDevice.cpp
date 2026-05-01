#include "gbepch.h"
#include "Platform/OpenGL/OpenGLRenderDevice.h"

#include "glad/glad.h"
#include "Logging/Logging.h"
#include "Utils/FileUtils.h"

namespace GreyboxEngine
{
    static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Int: return GL_INT;
        case ShaderDataType::Int2: return GL_INT;
        case ShaderDataType::Int3: return GL_INT;
        case ShaderDataType::Int4: return GL_INT;
        case ShaderDataType::Byte4: return GL_UNSIGNED_BYTE;
        case ShaderDataType::Mat3: return GL_FLOAT;
        case ShaderDataType::Mat4: return GL_FLOAT;
        default:
            // You should handle errors or unknown types here
            assert(false && "Unknown ShaderDataType!");
            return 0;
        }
    }

    // Helper to determine how many attribute slots this type needs
    static uint32_t GetSlotCount(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Mat3: return 3;
        case ShaderDataType::Mat4: return 4;
        default:                   return 1;
        }
    }
    
    static uint32_t GetElementCount(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float: return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;
        case ShaderDataType::Int: return 1;
        case ShaderDataType::Int2: return 2;
        case ShaderDataType::Int3: return 3;
        case ShaderDataType::Int4: return 4;
        case ShaderDataType::Byte4: return 4; // Usually for colors (RGBA)
        case ShaderDataType::Mat3: return 3;
        case ShaderDataType::Mat4: return 4;
        default:
            assert(false && "Unknown ShaderDataType!");
            return 0;
        }
    }

    OpenGLRenderDevice::OpenGLRenderDevice()
    {
    }

    OpenGLRenderDevice::~OpenGLRenderDevice()
    {
        GBE_CORE_TRACE("Cleaning Up OpenGL Render Device");

        for (const auto& vao : m_vaos)
        {
            glDeleteVertexArrays(1, &vao.vaoId);
        }
        for (const auto& vbo : m_vbos)
        {
            glDeleteBuffers(1, &vbo.vboId);
        }

        for (const auto& ibo : m_ibos)
        {
            glDeleteBuffers(1, &ibo.iboId);
        }

        for (const auto& shaderProgram : m_shaderPrograms)
        {
            glDeleteProgram(shaderProgram.shaderProgram);
        }
        m_vaos.clear();
        m_vbos.clear();
        m_ibos.clear();

        m_shaderPrograms.clear();
    }

    VertexArrayHandle OpenGLRenderDevice::CreateVertexArray()
    {
        GLVertexArrayInternal handle{};
        glGenVertexArrays(1, &handle.vaoId);

        m_vaos.push_back(handle);

        return {handle.vaoId};
    }

    VertexBufferHandle OpenGLRenderDevice::CreateVertexBuffer()
    {
        GLVertexBufferInternal buffer{};
        glGenBuffers(1, &buffer.vboId);

        m_vbos.push_back(buffer);

        return {buffer.vboId};
    }

    VertexBufferHandle OpenGLRenderDevice::CreateVertexBuffer(void* data, uint32_t size)
    {
        GLVertexBufferInternal newBuffer{};
        newBuffer.size = size;

        glGenBuffers(1, &newBuffer.vboId);
        glBindBuffer(GL_ARRAY_BUFFER, newBuffer.vboId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        m_vbos.push_back(newBuffer);

        return {newBuffer.vboId};
    }

    IndexBufferHandle OpenGLRenderDevice::CreateIndexBuffer(uint32_t* indices, uint32_t count)
    {
        GLIndexBufferInternal newBuffer{};
        glGenBuffers(1, &newBuffer.iboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newBuffer.iboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);

        m_ibos.push_back(newBuffer);

        return {newBuffer.iboId};
    }

    void OpenGLRenderDevice::BindVertexArray(VertexArrayHandle handle)
    {
        glBindVertexArray(handle.id);
    }

    void OpenGLRenderDevice::BindVertexBuffer(VertexBufferHandle handle)
    {
        glBindBuffer(GL_ARRAY_BUFFER, handle.id);
    }

    void OpenGLRenderDevice::BindIndexBuffer(IndexBufferHandle handle)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle.id);
    }

    void OpenGLRenderDevice::UnbindVertexArray(VertexArrayHandle handle)
    {
        glBindVertexArray(0);
    }

    void OpenGLRenderDevice::UnbindVertexBuffer(VertexBufferHandle handle)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLRenderDevice::UnbindIndexBuffer(IndexBufferHandle handle)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLRenderDevice::SetVertexBufferData(VertexBufferHandle handle, const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, handle.id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void OpenGLRenderDevice::PassVertexLayout(const VertexLayout& layout)
    {
        const auto& attributes = layout.GetAttributes();
        uint32_t attributeIndex = 0; // The actual layout location in the shader
        
        for (int i = 0; i < attributes.size(); ++i)
        {
            const auto& attr = attributes[i];
            uint8_t count = GetElementCount(attr.type);
            uint32_t slotCount = GetSlotCount(attr.type);
            GLenum baseType = ShaderDataTypeToGLBaseType(attr.type);
            
            if (slotCount == 1) {
                // Standard Vector/Scalar logic
                glEnableVertexAttribArray(attributeIndex);
                glVertexAttribPointer(
                    attributeIndex,
                    count,
                    baseType,
                    attr.normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    (const void*)attr.offset
                );
                attributeIndex++;
            } else {
                // Matrix logic: A mat4 is 4 vec4s
                // Each "row" gets its own attribute index
                for (uint32_t i = 0; i < slotCount; i++) {
                    glEnableVertexAttribArray(attributeIndex);
                    glVertexAttribPointer(
                        attributeIndex,
                        slotCount, // e.g., for mat4, each row is 4 components
                        baseType,
                        attr.normalized ? GL_TRUE : GL_FALSE,
                        layout.GetStride(),
                        // Offset moves by the size of one row (e.g., sizeof(float) * 4)
                        (const void*)(attr.offset + sizeof(float) * slotCount * i)
                    );
                
                    // Crucial for matrices in instanced rendering:
                    // glVertexAttribDivisor(attributeIndex, 1); 
                
                    attributeIndex++;
                }
            }
        }
    }

    ShaderProgramHandle OpenGLRenderDevice::CreateShader(const std::string& name, const std::string& vertexSrc,
                                                         const std::string& fragmentSrc)
    {
        GLShaderProgramInternal glProgram;
        glProgram.name = name;

        // === Vertex Shader ===
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const char* cstr = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &cstr, NULL);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GBE_CORE_ERROR("Failed to compile vertex shader for {0}", name);
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            return {0};
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
            return {0};
        }

        // === Link Shaders ===
        glProgram.shaderProgram = glCreateProgram();
        glAttachShader(glProgram.shaderProgram, vertexShader);
        glAttachShader(glProgram.shaderProgram, fragmentShader);
        glLinkProgram(glProgram.shaderProgram);

        glGetProgramiv(glProgram.shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            GBE_CORE_ERROR("Failed to link fragment and vertex shader for {0}", name);
            glGetProgramInfoLog(glProgram.shaderProgram, 512, NULL, infoLog);
            return {0};
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        GBE_LOG_TRACE("Shader {0} Created", glProgram.name);

        m_shaderPrograms.push_back(glProgram);

        return {glProgram.shaderProgram};
    }

    ShaderProgramHandle OpenGLRenderDevice::CreateShaderFromFile(const std::string& name,
        const std::string& vertexSrcFilename, const std::string& fragmentSrcFilename)
    {
        const auto vertexCode = FileUtils::ReadFromFile(vertexSrcFilename);
        const auto fragmentCode = FileUtils::ReadFromFile(fragmentSrcFilename);

        return CreateShader(name, vertexCode, fragmentCode);
    }

    void OpenGLRenderDevice::BindShader(ShaderProgramHandle handle)
    {
        glUseProgram(handle.id);
    }

    void OpenGLRenderDevice::UnbindShader(ShaderProgramHandle handle)
    {
    }

    void OpenGLRenderDevice::Draw(VertexArrayHandle vaoHandle, uint32_t vertexCount)
    {
        glBindVertexArray(vaoHandle.id);
        //glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
    }
}

#pragma once
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_precision.hpp> // <--- CRITICAL INCLUDE

namespace GreyboxEngine
{
    enum class ShaderDataType
    {
        Float,
        Float2,
        Float3,
        Float4,
        Int,
        Int2,
        Int3,
        Int4,
        Byte4,
        Mat3,
        Mat4
    };

    // 2. The InternalTraits "Translator"
    template <typename T>
    struct InternalTraits;

    template <>
    struct InternalTraits<float>
    {
        static constexpr ShaderDataType type = ShaderDataType::Float;
    };

    template <>
    struct InternalTraits<glm::vec2>
    {
        static constexpr ShaderDataType type = ShaderDataType::Float2;
    };

    template <>
    struct InternalTraits<glm::vec3>
    {
        static constexpr ShaderDataType type = ShaderDataType::Float3;
    };

    template <>
    struct InternalTraits<glm::u8vec4>
    {
        static constexpr ShaderDataType type = ShaderDataType::Byte4;
    };

    template <>
    struct InternalTraits<glm::mat3>
    {
        static constexpr ShaderDataType type = ShaderDataType::Mat3;
    };

    template <>
    struct InternalTraits<glm::mat4>
    {
        static constexpr ShaderDataType type = ShaderDataType::Mat4;
    };

    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };
    
    struct VertexAttribute
    {
        ShaderDataType type;
        bool normalized;
        size_t offset;
    };

    class VertexLayout
    {
    public:
        VertexLayout() : m_stride(0)
        {
        }

        template <typename T>
        void Push(bool normalized = false)
        {
            ShaderDataType type = InternalTraits<T>::type;

            m_attributes.push_back({type, normalized, m_stride});
            m_stride += sizeof(T);
        }

        inline const std::vector<VertexAttribute>& GetAttributes() const { return m_attributes; }
        inline unsigned int GetStride() const { return m_stride; }

    private:
        std::vector<VertexAttribute> m_attributes;
        unsigned int m_stride;
    };
}

#include "gbepch.h"
#include "Application/Application.h"

#include <cstdio>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ImGui/ImGuiLayer.h"
#include "Input/Input.h"
#include "Logging/Logging.h"
#include "Platform/PlatformUtils.h"
#include "Window/Window.h"
#include "Window/Events/Event.h"
#include "Input/KeyCode.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace GreyboxEngine
{
    Application* Application::s_instance = nullptr;

    Application::Application()
    {
        GreyboxEngine::Logging::Init();
        s_instance = this;

        // Window Creation
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(GBE_BIND_EVENT_FN(&Application::OnEvent));

        // ImGui Layer
        m_imGuiLayer = new ImGuiLayer();
        PushOverlay(m_imGuiLayer);
    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_layerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::PopLayer(Layer* layer)
    {
        m_layerStack.PopLayer(layer);
        layer->OnDetach();
    }

    void Application::PopOverlay(Layer* layer)
    {
        m_layerStack.PopOverlay(layer);
        layer->OnDetach();
    }

    void Application::ProcessEventQueue()
    {
        while (!m_eventQueue.empty())
        {
            auto& e = m_eventQueue.front();

            //GBE_CORE_INFO("{0}", e.ToString());

            bool handled = m_eventDispatcher.Dispatch<WindowCloseEvent>(
                e,GBE_BIND_EVENT_FN(&Application::OnWindowCloseEvent));
            if (!handled)
            {
                for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
                {
                    (*--it)->OnEvent(e);
                    if (e.handled)
                        break;
                }
            }

            m_eventQueue.pop();
        }
    }

    void Application::OnEvent(Event e)
    {
        m_eventQueue.push(e);
    }

    bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
    {
        m_running = false;
        return true;
    }

    void Application::Run()
    {
        // TEST CODE BEGIN

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";


        float vertices[] = {
            0.5f, 0.5f, 0.0f, // top right
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f // top left 
        };
        unsigned int indices[] = {
            // note that we start from 0!
            0, 1, 3, // first Triangle
            1, 2, 3 // second Triangle
        };

        // SHADER
        auto shader = CreateShader<OpenGLShader>("TestShader", vertexShaderSource, fragmentShaderSource);
        
        auto vertexArray = VertexArray::Create();
        vertexArray->Bind();

        auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices));

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        vertexBuffer->Unbind();
        vertexArray->Unbind();

        // TEST CODE END
        while (m_running)
        {
            m_window->Begin();

            // TEST CODE BEGIN

            glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);


            // TEST CODE END

            ProcessEventQueue();

            const float time = Time::GetTime();

            for (Layer* layer : m_layerStack)
            {
                layer->OnUpdate(time);
            }

            /* ImGui Begin */
            m_imGuiLayer->Begin();

            m_imGuiLayer->OnImGuiRender();

            m_imGuiLayer->End();
            /* ImGui End */

            m_window->OnUpdate();

            m_window->End();
        }

        Shutdown();
    }

    void Application::Shutdown()
    {
    }
}

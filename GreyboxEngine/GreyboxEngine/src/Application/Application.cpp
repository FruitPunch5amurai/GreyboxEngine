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
#include "Renderer/RenderDevice.h"
#include "Renderer/VertexLayout.h"

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

        Vertex vertices[] = {
            { { 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f} }, // top right
            { { 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f} }, // bottom right
            { {-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f} }, // bottom left
            { { -0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f} }  // top  left
        };
        
        unsigned int indices[] = {
            // note that we start from 0!
            0, 1, 3, // first Triangle
            1, 2, 3 // second Triangle
        };

        VertexLayout vertexLayout;
        vertexLayout.Push<glm::vec3>(); // Position
        vertexLayout.Push<glm::vec3>(); // Color

        // SHADER
        auto device = RenderDevice::Create();
        //const auto shaderId = device->CreateShader("TestShader", vertexShaderSource, fragmentShaderSource);
        const auto shaderId = device->CreateShaderFromFile("TestShader",
            "Assets/Shaders/TestVertexShader",
            "Assets/Shaders/TestFragmentShader");

        auto vaoId = device->CreateVertexArray();
        device->BindVertexArray(vaoId);

        auto vboId = device->CreateVertexBuffer(vertices, sizeof(vertices));
        auto iboId = device->CreateIndexBuffer(indices, sizeof(indices));        

        device->BindVertexBuffer(vboId);

        device->PassVertexLayout(vertexLayout);
        
        device->UnbindVertexBuffer(vboId);

        device->UnbindVertexArray(vaoId);

        // TEST CODE END
        while (m_running)
        {
            m_window->Begin();

            // TEST CODE BEGIN

            glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            device->BindShader(shaderId);
            device->Draw(vaoId, 6);

            // TEST CODE END
            
            ProcessEventQueue();

            const float time = Time::GetTime();

            for (Layer* layer : m_layerStack)
            {
                layer->OnUpdate(time);
            }

            m_imGuiLayer->Begin();

            m_imGuiLayer->OnImGuiRender();

            m_imGuiLayer->End();

            m_window->OnUpdate();

            m_window->End();
        }

        Shutdown();
    }

    void Application::Shutdown()
    {
    }
}

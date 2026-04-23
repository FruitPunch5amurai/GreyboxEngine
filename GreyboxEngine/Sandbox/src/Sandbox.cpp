#include <GreyboxEngine.h>


class TestLayer : public GreyboxEngine::Layer
{
public:
    TestLayer() : Layer("TestLayer"){}

    void OnUpdate() override
    {
        GBE_LOG_INFO("TestLayer::Update");
    }

    void OnEvent(GreyboxEngine::Event& event) override
    {
        GBE_LOG_TRACE("{0}", event.ToString());
    }
};

class Sandbox : public GreyboxEngine::Application
{
public:
    Sandbox()
    {
        PushLayer(new TestLayer());
        PushOverlay(new GreyboxEngine::ImGuiLayer());
    }
    ~Sandbox(){}
};


GreyboxEngine::Application* GreyboxEngine::CreateApplication()
{
    return new Sandbox();
}

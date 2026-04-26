#include <GreyboxEngine.h>

class TestLayer : public GreyboxEngine::Layer
{
public:
    TestLayer() : Layer("TestLayer"){}
    ~TestLayer() override {}
    
    void OnUpdate(float time) override
    {

    }

    void OnEvent(GreyboxEngine::Event& event) override
    {

    }
};

class Sandbox : public GreyboxEngine::Application
{
public:
    Sandbox()
    {
        PushOverlay(new GreyboxEngine::ImGuiLayer());
    }
    ~Sandbox(){}
};


GreyboxEngine::Application* GreyboxEngine::CreateApplication()
{
    return new Sandbox();
}

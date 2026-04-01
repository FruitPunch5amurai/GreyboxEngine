#include <GreyboxEngine.h>


class Sandbox : public GreyboxEngine::Application
{
public:
    Sandbox(){}
    ~Sandbox(){}
};


GreyboxEngine::Application* GreyboxEngine::CreateApplication()
{
    return new Sandbox();
}

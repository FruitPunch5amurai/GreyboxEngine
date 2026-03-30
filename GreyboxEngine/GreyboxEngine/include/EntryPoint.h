#pragma once

#ifdef GBE_PLATFORM_WINDOWS

extern GreyboxEngine::Application* GreyboxEngine::CreateApplication();

int main(int argc, char* argv[])
{
    const auto app = GreyboxEngine::CreateApplication();
    app->Run();
    delete app;
}
#endif
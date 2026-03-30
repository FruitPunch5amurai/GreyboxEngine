#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"

namespace  GreyboxEngine
{
    class GBE_API Logging
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> & GetEngineLogger() {return s_EngineLogger;}
        inline static std::shared_ptr<spdlog::logger> & GetClientLogger() {return s_ClientLogger;}

    private:
        static  std::shared_ptr<spdlog::logger> s_EngineLogger;
        static  std::shared_ptr<spdlog::logger> s_ClientLogger;
        
    };
}

// For use by Engine
#define GBE_ERROR(...) ::GreyboxEngine::Logging::GetEngineLogger()->error(__VA_ARGS__)
#define GBE_WARN(...) ::GreyboxEngine::Logging::GetEngineLogger()->warn(__VA_ARGS__)
#define GBE_INFO(...) ::GreyboxEngine::Logging::GetEngineLogger()->info(__VA_ARGS__)

// For use by Client
#define GBE_LOG_ERROR(...) ::GreyboxEngine::Logging::GetClientLogger()->error(__VA_ARGS__)
#define GBE_LOG_WARN(...) ::GreyboxEngine::Logging::GetClientLogger()->warn(__VA_ARGS__)
#define GBE_LOG_INFO(...) ::GreyboxEngine::Logging::GetClientLogger()->info(__VA_ARGS__)
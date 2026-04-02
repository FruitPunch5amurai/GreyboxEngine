#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"

namespace  GreyboxEngine
{
    class GBE_API Logging
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> & GetCoreLogger() {return s_CoreLogger;}
        inline static std::shared_ptr<spdlog::logger> & GetClientLogger() {return s_ClientLogger;}
 
    private:
        static  std::shared_ptr<spdlog::logger> s_CoreLogger;
        static  std::shared_ptr<spdlog::logger> s_ClientLogger;
        
    };
}

// For use by Engine
#define GBE_CORE_ERROR(...) ::GreyboxEngine::Logging::GetCoreLogger()->error(__VA_ARGS__)
#define GBE_CORE_WARN(...) ::GreyboxEngine::Logging::GetCoreLogger()->warn(__VA_ARGS__)
#define GBE_CORE_INFO(...) ::GreyboxEngine::Logging::GetCoreLogger()->info(__VA_ARGS__)

// For use by Client
#define GBE_LOG_ERROR(...) ::GreyboxEngine::Logging::GetClientLogger()->error(__VA_ARGS__)
#define GBE_LOG_WARN(...) ::GreyboxEngine::Logging::GetClientLogger()->warn(__VA_ARGS__)
#define GBE_LOG_INFO(...) ::GreyboxEngine::Logging::GetClientLogger()->info(__VA_ARGS__)
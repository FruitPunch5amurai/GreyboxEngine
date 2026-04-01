#include "gbepch.h"
#include "Logging/Logging.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace GreyboxEngine
{
    std::shared_ptr<spdlog::logger> Logging::s_EngineLogger;
    
    std::shared_ptr<spdlog::logger> Logging::s_ClientLogger;


    void Logging::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        
       s_EngineLogger = spdlog::stdout_color_mt("Engine");
        s_EngineLogger->set_level(spdlog::level::trace);
       
       s_ClientLogger = spdlog::stdout_color_mt("Client");
       s_ClientLogger->set_level(spdlog::level::trace);
    }
}

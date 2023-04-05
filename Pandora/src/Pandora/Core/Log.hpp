#pragma once

#include "Pandora/Core/Base.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Pandora {

    class Log
    {
    public:
        static void Init();

        static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
    };
}

#define PD_CORE_TRACE(...)    ::Pandora::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PD_CORE_INFO(...)     ::Pandora::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PD_CORE_WARN(...)     ::Pandora::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PD_CORE_ERROR(...)    ::Pandora::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PD_CORE_CRITICAL(...) ::Pandora::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define PD_TRACE(...)         ::Pandora::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PD_INFO(...)          ::Pandora::Log::GetClientLogger()->info(__VA_ARGS__)
#define PD_WARN(...)          ::Pandora::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PD_ERROR(...)         ::Pandora::Log::GetClientLogger()->error(__VA_ARGS__)
#define PD_CRITICAL(...)      ::Pandora::Log::GetClientLogger()->critical(__VA_ARGS__)

#pragma once

#include "Pandora/Core/PlatformDetection.hpp"

#include <memory>

#ifdef PD_DEBUG
	#if defined(PD_PLATFORM_WINDOWS)
		#define PD_DEBUGBREAK() __debugbreak()
	#elif defined(PD_PLATFORM_LINUX)
		#include <signal.h>
		#define PD_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define PD_ENABLE_ASSERTS
#else
	#define PD_DEBUGBREAK()
#endif

#define PD_EXPAND_MACRO(x) x
#define PD_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define PD_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#ifdef PD_ENABLE_ASSERTS
	#define PD_ASSERT(x, ...) { if(!(x)) { PD_ERROR("Assertion Failed: {0}", __VA_ARGS__); PD_DEBUGBREAK(); } }
	#define PD_CORE_ASSERT(x, ...) { if(!(x)) { PD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); PD_DEBUGBREAK(); } }
#else
	#define PD_ASSERT(x, ...)
	#define PD_CORE_ASSERT(x, ...)
#endif

namespace Pandora {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Log.hpp"
#pragma once

#include "crystal/core/Base.h"
#include "glm/gtx/string_cast.hpp"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

using namespace std;
using namespace spdlog;

namespace Crystal {
	class Log
	{
	public:
		static void Init();

		static Reference<logger>& GetCoreLogger() { return coreLogger; }
		static Reference<logger>& GetClientLogger() { return clientLogger; }
	
	private:
		static Reference<logger> clientLogger;
		static Reference<logger> coreLogger;
	};
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::vec<L, T, Q>& vector)
{
	return stream << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::mat<C, R, T, Q>& matrix)
{
	return stream << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, glm::qua<T, Q> quaternion)
{
	return stream << glm::to_string(quaternion);
}

#define CRYSTAL_CORE_ERROR(...)	Crystal::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CRYSTAL_CORE_WARNING(...)	Crystal::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CRYSTAL_CORE_INFO(...)	Crystal::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CRYSTAL_CORE_TRACE(...) Crystal::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CRYSTAL_CORE_CRITICAL(...) Crystal::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define CRYSTAL_ERROR(...)	Crystal::Log::GetClientLogger()->error(__VA_ARGS__)
#define CRYSTAL_WARN(...)	Crystal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CRYSTAL_INFO(...)	Crystal::Log::GetClientLogger()->info(__VA_ARGS__)
#define CRYSTAL_TRACE(...)	Crystal::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CRYSTAL_CRITICAL(...)	Crystal::Log::GetClientLogger()->critical(__VA_ARGS__)

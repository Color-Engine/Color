#pragma once

#include "Core/Base.h"
#include "Misc/MessageDialog.h"

#pragma warning(push, 0)
#define FMT_DEPRECATED_OSTREAM
#define SPDLOG_FMT_EXTERNAL
#define SPDLOG_LEVEL_NAMES { "trace", "debug", "info", "warning", "error", "fatal", "off" }
#define SPDLOG_SHORT_LEVEL_NAMES { "T", "D", "I", "W", "E", "F", "O" } 
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

namespace Color
{
	namespace Log
	{
		inline Ref<spdlog::logger> g_CoreLogger, g_ClientLogger;
		void Init();

		// Don't call manually, this is an internal function!
		void DebugNotifyFatalLog();

		// Don't call manually, this is an internal function!
		template <typename... Args>
		void RuntimeErrorLog(const Ref<spdlog::logger>& logger, bool fatal, std::string_view format, Args&&... args)
		{
			std::string message = fmt::vformat(format, fmt::make_format_args(args...));
			if (fatal)
			{
				message += std::string("\n\nLogged by: ") + logger->name() + "\nThe application will be aborted due to that.";
			}
			Ref<MessageDialog> dialog = MessageDialog::New(fatal ? "Fatal error!" : "Runtime error!", message, DialogControls::Ok, DialogIcon::Error);
			dialog->CreateAndWait();

			if (fatal)
			{
				std::exit(EXIT_FAILURE);
			}
		}
	}
}

template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::vec<L, T, Q>& vector)
{
	return stream << glm::to_string(vector);
}

template <typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::mat<C, R, T, Q>& matrix)
{
	return stream << glm::to_string(matrix);
}

template <typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::qua<T, Q>& quaternion)
{
	return stream << glm::to_string(quaternion);
}

#ifdef CL_TEST_BUILD

#define CL_LOGGER_TRACE(logger, ...)   logger->trace(__VA_ARGS__)
#define CL_LOGGER_INFO(logger, ...)    logger->info(__VA_ARGS__)
#define CL_LOGGER_WARN(logger, ...)    logger->warn(__VA_ARGS__)
#define CL_LOGGER_ERROR(logger, ...)   logger->error(__VA_ARGS__)
#define CL_LOGGER_FATAL(logger, ...) { logger->error(__VA_ARGS__); ::Color::Log::DebugNotifyFatalLog(); }

#else

#define CL_LOGGER_TRACE(logger, ...)
#define CL_LOGGER_INFO(logger, ...)
#define CL_LOGGER_WARN(logger, ...)
#define CL_LOGGER_ERROR(logger, ...) ::Color::Log::RuntimeErrorLog(logger, false, __VA_ARGS__)
#define CL_LOGGER_FATAL(logger, ...) ::Color::Log::RuntimeErrorLog(logger, true, __VA_ARGS__)

#endif

#define CL_CORE_TRACE(...) CL_LOGGER_TRACE(::Color::Log::g_CoreLogger, __VA_ARGS__)
#define CL_CORE_INFO(...)  CL_LOGGER_INFO (::Color::Log::g_CoreLogger, __VA_ARGS__)
#define CL_CORE_WARN(...)  CL_LOGGER_WARN (::Color::Log::g_CoreLogger, __VA_ARGS__)
#define CL_CORE_ERROR(...) CL_LOGGER_ERROR(::Color::Log::g_CoreLogger, __VA_ARGS__)
#define CL_CORE_FATAL(...) CL_LOGGER_FATAL(::Color::Log::g_CoreLogger, __VA_ARGS__)

#define CL_TRACE(...)      CL_LOGGER_TRACE(::Color::Log::g_ClientLogger, __VA_ARGS__)
#define CL_INFO(...)       CL_LOGGER_INFO (::Color::Log::g_ClientLogger, __VA_ARGS__)
#define CL_WARN(...)       CL_LOGGER_WARN (::Color::Log::g_ClientLogger, __VA_ARGS__)
#define CL_ERROR(...)      CL_LOGGER_ERROR(::Color::Log::g_ClientLogger, __VA_ARGS__)
#define CL_FATAL(...)      CL_LOGGER_FATAL(::Color::Log::g_ClientLogger, __VA_ARGS__)

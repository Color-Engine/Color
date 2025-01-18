#include "EnginePCH.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Color::Log
{
	void Init()
	{
		spdlog::sink_ptr sinks[] =
		{
			MakeRef<spdlog::sinks::stdout_color_sink_mt>(),
			MakeRef<spdlog::sinks::basic_file_sink_mt>("Color-Runtime.log", true)
		};

		sinks[0]->set_pattern("%^[%T] %n: %v%$");
		sinks[1]->set_pattern("[%T] (%l) %n: %v");

		auto CreateLogger = [sinks](const std::string& name) -> Ref<spdlog::logger>
		{
			Ref<spdlog::logger> logger = MakeRef<spdlog::logger>(name, begin(sinks), end(sinks));
			spdlog::register_logger(logger);

			logger->set_level(spdlog::level::trace);
			logger->flush_on(spdlog::level::trace);

			return logger;
		};

		g_CoreLogger   = CreateLogger("ENGINE");
		g_ClientLogger = CreateLogger("CLIENT");
	}

	void DebugNotifyFatalLog()
	{
		std::cout << "  -> The application will be aborted due to that.\n";
		std::exit(EXIT_FAILURE);
	}
}

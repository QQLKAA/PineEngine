#pragma once

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Pine {

class Log {
public:
  static void init();

  inline static std::shared_ptr<spdlog::logger> getEngineLogger() {
    return s_engineLogger;
  }

  inline static std::shared_ptr<spdlog::logger> getAppLogger() {
    return s_appLogger;
  }

private:
  static std::shared_ptr<spdlog::logger> s_engineLogger;
  static std::shared_ptr<spdlog::logger> s_appLogger;
};

}

#define PINE_TRACE(...) Pine::Log::getEngineLogger()->trace(__VA_ARGS__)
#define PINE_DEBUG(...) Pine::Log::getEngineLogger()->debug(__VA_ARGS__)
#define PINE_INFO(...) Pine::Log::getEngineLogger()->info(__VA_ARGS__)
#define PINE_WARN(...) Pine::Log::getEngineLogger()->warn(__VA_ARGS__)
#define PINE_ERROR(...) Pine::Log::getEngineLogger()->error(__VA_ARGS__)
#define PINE_CRITICAL(...) Pine::Log::getEngineLogger()->critical(__VA_ARGS__)

#define APP_TRACE(...) Pine::Log::getAppLogger()->trace(__VA_ARGS__)
#define APP_DEBUG(...) Pine::Log::getAppLogger()->debug(__VA_ARGS__)
#define APP_INFO(...) Pine::Log::getAppLogger()->info(__VA_ARGS__)
#define APP_WARN(...) Pine::Log::getAppLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...) Pine::Log::getAppLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...) Pine::Log::getAppLogger()->critical(__VA_ARGS__)

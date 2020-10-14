#include <pine.h>

namespace Pine {

std::shared_ptr<spdlog::logger> Log::s_engineLogger;
std::shared_ptr<spdlog::logger> Log::s_appLogger;
std::shared_ptr<spdlog::logger> Log::s_openGLLogger;

void Log::init() {
  s_engineLogger = spdlog::stdout_color_mt("Pine");
  s_engineLogger->set_level(spdlog::level::trace);

  s_appLogger = spdlog::stdout_color_mt("App");
  s_appLogger->set_level(spdlog::level::trace);

  s_openGLLogger = spdlog::stdout_color_mt("OpenGL");
  s_openGLLogger->set_level(spdlog::level::trace);
}

}

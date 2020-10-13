#include <pine.h>
#include <spdlog/spdlog.h>

int main() {
  Pine::Log::init();

  bool error;
  Pine::Window window(error, 1280, 720, "PineEngine Sandbox");
  if (error) {
    return 1;
  }

  APP_INFO("Error is {}", error);

  while (window.isOpen()) {
    window.update();
  }

  return 0;
}

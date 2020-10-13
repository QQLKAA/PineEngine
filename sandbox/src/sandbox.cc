#include <pine.h>
#include <spdlog/spdlog.h>

int main() {
  bool error;
  Pine::Window window(error, 1280, 720, "PineEngine Sandbox");
  if (error) {
    return 1;
  }

  spdlog::info("Hello, world!");

  while (window.isOpen()) {
    window.update();
  }

  return 0;
}

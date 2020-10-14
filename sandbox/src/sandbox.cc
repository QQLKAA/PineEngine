#include <glad/glad.h>
#include <pine.h>

int main() {
  Pine::Log::init();

  bool error;
  Pine::Window window(error, 1280, 720, "PineEngine Sandbox");
  if (error) {
    return 1;
  }

  APP_INFO("Error is {}", error);

  while (window.isOpen()) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    window.update();
  }

  return 0;
}

#include <pine.h>

int main() {
  bool error;
  Pine::Window window(error, 1280, 720, "PineEngine Sandbox");
  if (error) {
    return 1;
  }

  while (window.isOpen()) {
    window.update();
  }

  return 0;
}

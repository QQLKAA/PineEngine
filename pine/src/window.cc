#include <pine.h>

namespace Pine {

Window::Window(
    bool& error, int width, int height, const std::string_view title) {
  if (glfwInit() != GLFW_TRUE) {
    error = true;
    return;
  }

  _handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
  if (!_handle) {
    error = true;
    return;
  }
  
  error = false;
}  

Window::~Window() {
  if (_handle != nullptr) {
    glfwDestroyWindow(_handle);
    _handle = nullptr;
  }
  glfwTerminate();
}

bool Window::isOpen() const {
  return glfwWindowShouldClose(_handle) == GLFW_FALSE;
}

void Window::update() {
  glfwPollEvents();
}

void Window::close() {
  glfwSetWindowShouldClose(_handle, GLFW_TRUE);
}

}

#include <pine.h>

namespace Pine {

Window::Window(
    bool& error, int width, int height, const std::string_view title) {
  PINE_INFO("Creating window with size ({}, {}) and title \"{}\"",
            width, height, title);
  
  if (glfwInit() != GLFW_TRUE) {
    const char* msg;
    glfwGetError(&msg);
    PINE_ERROR("Failed to initialize GLFW: {}", msg);
    error = true;
    return;
  }

  _handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
  if (!_handle) {
    const char* msg;
    glfwGetError(&msg);
    PINE_ERROR("Failed to create window: {}", msg);
    error = true;
    return;
  }
  
  error = false;
}  

Window::~Window() {
  PINE_TRACE("Destroying window");

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

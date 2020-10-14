#include <pine.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pine {

static void GLAPIENTRY MessageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam ) {
  switch (severity) {
    case GL_DEBUG_SEVERITY_NOTIFICATION: {
      OGL_TRACE(message);
    } break;
    case GL_DEBUG_SEVERITY_LOW: {
      OGL_INFO(message);
    } break;
    case GL_DEBUG_SEVERITY_MEDIUM: {
      OGL_WARN(message);
    } break;
    case GL_DEBUG_SEVERITY_HIGH: {
      OGL_ERROR(message);
    } break;
  }
}

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

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
  if (!_handle) {
    const char* msg;
    glfwGetError(&msg);
    PINE_ERROR("Failed to create window: {}", msg);
    error = true;
    return;
  }
  glfwMakeContextCurrent(_handle);
  
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glDebugMessageCallback(MessageCallback, nullptr);
  glEnable(GL_DEBUG_OUTPUT);
  
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
  glfwSwapBuffers(_handle);
  glfwPollEvents();
}

void Window::close() {
  glfwSetWindowShouldClose(_handle, GLFW_TRUE);
}

}

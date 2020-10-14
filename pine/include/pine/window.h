#pragma once

#include <string_view>

class GLFWwindow;

namespace Pine {

class Window {
public:
  Window(bool& error, int width, int height, const std::string_view title);
  virtual ~Window();

  Window(const Window&) = delete;
  Window& operator =(const Window&) = delete;

  bool isOpen() const;
  void update();
  void close();

private:
  GLFWwindow* _handle = nullptr;
};

}

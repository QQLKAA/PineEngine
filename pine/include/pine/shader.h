#pragma once

#include <cstdint>
#include <string_view>

namespace Pine {

class Shader {
public:
  Shader(bool& error, const std::string_view path);
  virtual ~Shader();

  void bind();

private:
  bool compileShader(const std::string_view type, const std::string_view src);

private:
  uint32_t _programId;
};

}

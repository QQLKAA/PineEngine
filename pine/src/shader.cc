#include <glad/glad.h>
#include <pine.h>
#include <fstream>
#include <string>
#include <map>

namespace Pine {

Shader::Shader(bool& error, const std::string_view path) {
  PINE_INFO("Loading shader from {}", path);

  std::ifstream file(path.data());
  if (!file.is_open()) {
    PINE_ERROR("Failed to open file {}", path);
    error = true;
    return;
  }

  _programId = glCreateProgram();
  
  std::map<std::string, std::string> shaderSources;

  std::string currentShaderType = "";
  std::string line;
  while (std::getline(file, line)) {
    std::string_view line_view(line);

    if (line_view.substr(0, 7).compare("#shader") == 0) {
      currentShaderType = line_view.substr(8);
      shaderSources[currentShaderType] = "";
    } else if (currentShaderType.length() > 0) {
      shaderSources[currentShaderType] += line + "\n";
    }
  }
  file.close();

  for (auto& source: shaderSources) {
    if (!compileShader(source.first, source.second)) {
      error = true;
      return;
    }
  }

  PINE_TRACE("Linking shader program");
  glLinkProgram(_programId);

  int linkStatus;
  glGetProgramiv(_programId, GL_LINK_STATUS, &linkStatus);
  if (linkStatus != GL_TRUE) {
    int length;
    glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &length);
    std::string msg(length, '\0');
    glGetProgramInfoLog(_programId, length, nullptr, &msg[0]);
    PINE_ERROR("Failed to link program: {}", msg);
  }

  error = false;
}

Shader::~Shader() {
  glDeleteProgram(_programId);
  _programId = 0;
}

void Shader::bind() {
  glUseProgram(_programId);
}

bool Shader::compileShader(
    const std::string_view type, const std::string_view src) {
  PINE_TRACE("Compilling {} shader", type);
  GLenum shaderType = 
      type == "vertex" ? GL_VERTEX_SHADER :
      type == "fragment" ? GL_FRAGMENT_SHADER :
      type == "geometry" ? GL_GEOMETRY_SHADER :
      type == "compute" ? GL_COMPUTE_SHADER :
      type == "tess_control" ? GL_TESS_CONTROL_SHADER :
      type == "tess_evaulation" ? GL_TESS_EVALUATION_SHADER :
      GL_INVALID_ENUM;
  if (shaderType == GL_INVALID_ENUM) {
    PINE_WARN("Unknown shader type ({}), skipping", type);
    return true;
  }

  uint32_t shader = glCreateShader(shaderType);
  const char* srcPtr = src.data();
  glShaderSource(shader, 1, &srcPtr, nullptr);
  glCompileShader(shader);

  int compileStatus;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
  if (compileStatus != GL_TRUE) {
    int length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    std::string msg(length, '\0');
    glGetShaderInfoLog(shader, length, nullptr, &msg[0]);
    PINE_ERROR("Failed to compile {} shader: {}", type, msg);

    glDeleteShader(shader);
    return false;
  }

  glAttachShader(_programId, shader);
  glDeleteShader(shader);

  return true;
}

}

#include <glad/glad.h>
#include <pine.h>

int main() {
  Pine::Log::init();

  bool error;
  Pine::Window window(error, 1280, 720, "PineEngine Sandbox");
  if (error) {
    return 1;
  }
  
  auto shader = std::make_shared<Pine::Shader>(
      error, "assets/shaders/basic.glsl");
  if (error) {
    return 1;
  }

  while (window.isOpen()) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const float verts[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
    };

    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 
                          reinterpret_cast<void*>(0));
    
    shader->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    window.update();
  }

  return 0;
}

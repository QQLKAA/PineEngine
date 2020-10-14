#shader vertex
#version 450 core

layout(location = 0) in vec3 aPosition;

void main() {
  gl_Position = vec4(aPosition, 1);
}

#shader fragment
#version 450 core

out vec4 fColor;

void main() {
  fColor = vec4(1, 0, 0, 1);
}

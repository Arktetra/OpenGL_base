#version 330 core
layout (location = 0) in vec3 a_pos;

out float height;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    height = a_pos.y;
    position = (view * model * vec4(a_pos, 1.0)).xyz;
    gl_Position = projection * view * model * vec4(a_pos, 1.0);
}
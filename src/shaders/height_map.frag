#version 330 core

out vec4 frag_color;

in float height;

void main() {
    float h = (height + 16) / 64.0;
    // float h = height / 256.0;
    frag_color = vec4(h, h, h, 1.0);
}
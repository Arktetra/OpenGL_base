#version 410 core

in float Height;

out vec4 FragColor;

float random(float height) {
    return fract(sin(height * 2.0));
}

void main()
{
    float h = (Height + 16)/64.0f;
    float rnd = random(h);

    // FragColor = vec4(h, h, h, 1.0);
    FragColor = vec4(rnd, rnd, rnd, 1.0);
}
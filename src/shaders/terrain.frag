#version 330 core
out vec4 FragColor;

in float height;

void main()
{
	float h = height / 64;
	FragColor = vec4(h, h, h, 1.0);
}
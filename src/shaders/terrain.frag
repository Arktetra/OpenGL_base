#version 330 core
out vec4 FragColor;

in float height;
in vec2 tex_coord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float height_0 = 64.0;
uniform float height_1 = 160.0;
uniform float height_2 = 256.0;

vec4 calc_texture_color();


void main() {
	float h = height / 256;
	FragColor = calc_texture_color();
}

vec4 calc_texture_color() {
	vec4 texture_color;

	if (height < height_0) {
		texture_color = texture(texture0, tex_coord);
	} else if (height < height_1) {
		vec4 color_0 = texture(texture0, tex_coord);
		vec4 color_1 = texture(texture1, tex_coord);
		texture_color = mix(color_0, color_1, (height - height_0) / (height_1 - height_0));
	} else if (height < height_2) {
		vec4 color_0 = texture(texture1, tex_coord);
		vec4 color_1 = texture(texture2, tex_coord);
		texture_color = mix(color_0, color_1, (height - height_1) / (height_2 - height_1));
	} else {
		texture_color = texture(texture2, tex_coord);
	}

	return texture_color;
}
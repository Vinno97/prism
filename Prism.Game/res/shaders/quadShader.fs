#version 330 core

in vec2 UV;

out vec4 color;

layout(binding = 0) uniform sampler2D image1;
layout(binding = 1) uniform sampler2D image2;

void main(){
	vec4 t0 = texture(image1, UV);
	vec4 t1 = texture(image2, UV);
    color = t0 * 0.9 + t1 * 0.1;
}

#version 420 core

in vec2 UV;

out vec4 color;

layout(binding = 0) uniform sampler2D image1;

void main(){
	color = texture(image1, UV);
}

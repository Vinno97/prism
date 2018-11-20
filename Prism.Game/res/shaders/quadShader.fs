#version 330 core

in vec2 UV;
out vec4 color;

uniform vec3 ambientLightColor;
uniform float ambientLightStrength;
uniform vec3 sunPosition;
uniform vec3 sunColor;

layout(binding = 0) uniform sampler2D gPosition;

void main(){

    vec3 FragPos = texture(gPosition, UV).rgb;
	color = vec4(FragPos, 1.0);
}
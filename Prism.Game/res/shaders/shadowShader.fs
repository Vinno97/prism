#version 420 core

layout(location = 0) out vec3 gPosition;
in vec4 fragPos;

void main() {
	gPosition = fragPos.xyz;
}


#version 420 core
layout(location = 0) out vec3 gPosition;

uniform vec3 objectColor;

in vec3 fragPos;  
in vec3 normal;  

void main() {
	gPosition = fragPos;
}

#version 330 core
layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec3 gAlbedo;
layout(location = 3) out float gDepth;

uniform vec3 objectColor;

in vec3 fragPos;  
in vec3 normal;  

void main() {
	gPosition = fragPos;
	gDepth = gPosition.z;
	gNormal = normal;
	gAlbedo = objectColor;
}
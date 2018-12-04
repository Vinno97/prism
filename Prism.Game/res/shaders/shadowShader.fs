#version 330 core
layout(location = 0) out float fragmentdepth;
in vec3 fragPos;  

void main() {
	fragmentdepth = fragPos.z;
}


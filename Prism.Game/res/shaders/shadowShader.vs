#version 420 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj; 

out vec4 fragPos;

void main() { 
	fragPos = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1 ); 
	gl_Position = fragPos;
}



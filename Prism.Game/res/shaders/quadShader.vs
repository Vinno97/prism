#version 330 core

layout (location = 0) in vec3 aPos; 
out vec2 UV;

void main() { 
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1 ); 
	UV = vec2((aPos.x+1.0)/2.0, 1 - (aPos.y+1.0/2.0));
}
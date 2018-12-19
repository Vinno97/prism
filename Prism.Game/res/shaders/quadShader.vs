#version 420 core

layout (location = 0) in vec2 aPos; 
layout (location = 1) in vec2 tex; 
out vec2 UV;
uniform mat4 bias; 

void main() { 
	gl_Position = vec4(aPos.x, aPos.y, 0, 1 ); 
	UV = tex;
}
#version 330 core
layout (location = 0) in vec3 aPos; 
out vec4 pass_colour;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj; 
void main() { 
	gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1 ); 
	pass_colour = view * model * vec4(aPos.x, aPos.y, aPos.z, 1); 
}
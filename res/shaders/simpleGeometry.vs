#version 330 core
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 normal; 
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj; 

out vec3 FragPos;

void main() { 
	gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1 ); 
	FragPos = vec3(gl_Position.x, gl_Position.y, gl_Position.z);
}
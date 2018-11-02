#version 330 core
in vec4 pass_colour; 
out vec4 FragColor; 
void main() { 
	FragColor = pass_colour*-1; 
}
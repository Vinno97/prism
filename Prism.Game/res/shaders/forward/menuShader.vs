#version 330 core
layout (location = 0) in vec2 aPos;

out vec2 textureCoords;

uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = view * model * vec4(aPos.x, aPos.y, 0.0, 1.0);
	textureCoords = vec2((aPos.x+1.0)/2.0, 1 - (aPos.y+1.0/2.0));
}
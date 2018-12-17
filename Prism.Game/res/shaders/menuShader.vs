#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 UV;

out vec2 textureCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = model * vec4(aPos.x, aPos.y, 0.0, 1.0);
	textureCoords = UV;
}
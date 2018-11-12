#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = view * model * vec4(aPos.x, aPos.y, 0.0, 1.0);
}
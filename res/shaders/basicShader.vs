#version 150 core

in vec3 position;
in vec3 color;

out vec3 Color;

void main()
{
    gl_Position = vec4(position, 1);
    Color = color;
}
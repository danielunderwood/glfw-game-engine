#version 150 core

in vec3 vert;
in vec3 color;

out vec3 Color;

void main()
{
    gl_Position = vec4(vert, 1);
    Color = color;
}
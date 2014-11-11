#version 150 core

in vec3 position;
in vec3 color;

out vec3 Color;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(position, 1);
    Color = color;
}
#version 150 core

in vec3 Color;

out vec4 finalColor;

void main()
{
    finalColor = vec4(Color, 1.0);
}
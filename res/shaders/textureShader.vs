#version 150 core

in vec3 position;
in vec2 texCoord;

out vec2 texFrag;

void main()
{
    gl_Position = vec4(position, 1.0);
    texFrag = texCoord;
}
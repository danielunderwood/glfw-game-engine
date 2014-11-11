#version 150 core

in vec3 position;
in vec2 texCoord;

out vec2 texFrag;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(position, 1.0);
    texFrag = texCoord;
}
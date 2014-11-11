#version 150 core

in vec3 position;
in vec2 texCoord;

out vec2 texFrag;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    texFrag = texCoord;
}
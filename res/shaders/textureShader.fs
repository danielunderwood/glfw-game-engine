#version 150 core

in vec2 texFrag;

out vec4 finalColor;

uniform sampler2D tex;

void main()
{
    finalColor = texture(tex, texFrag);
}
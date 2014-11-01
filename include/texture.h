#pragma once

#include <glew.h>
#include <glfw3.h>

// Represents a texture
class Texture
{
public:
    Texture();
    ~Texture();

    // Getter for textureID
    GLuint getTextureID();

private:
    // OpenGL's ID for the texture
    GLuint textureID;
};
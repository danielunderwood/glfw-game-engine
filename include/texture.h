#pragma once

#include <glew.h>
#include <glfw3.h>

// Represents a texture
class Texture
{
public:
    Texture(const char * filename, GLenum textureType = GL_TEXTURE_2D);
    ~Texture();

    // Bind texture for use
    void bind();

    // Getter for textureID
    GLuint getTextureID();

private:
    // OpenGL's ID for the texture
    GLuint textureID;

    // Type identifier of texture
    GLenum textureType;

    // ID of Current Texture
    // TODO: Make this a texture object
    static GLuint currentTexture;
};
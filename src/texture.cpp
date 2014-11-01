#include <SOIL.h>
#include <stdio.h>
#include "texture.h"
#include "../deps/glfw/deps/EGL/eglext.h"

GLuint Texture::currentTexture = 0;

Texture::Texture(const char * filename, GLenum textureType) :
    textureType(textureType)
{
    // Generate OpenGL texture
    glGenTextures(1, &textureID);

    // Load Image
    // TODO: Error Handling
    printf("Loading %s as texture %d\n", filename, textureID);
    fflush(stdout);
    int height, width;
    unsigned char * texImage = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
    printf("%s successfully loaded\n", filename);

    // Assign Texture
    // TODO: Make this work with 1D and 3D textures
    glTexImage2D(textureType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);

    // Free Image Data
    SOIL_free_image_data(texImage);

    // Generate Mipmaps
    glGenerateMipmap(textureType);
}

Texture::~Texture()
{
    // Delete textures
    glDeleteTextures(textureType, &textureID);
}

void Texture::bind()
{
    currentTexture = textureID;
    glBindTexture(1, textureID);
}

GLuint Texture::getTextureID() { return textureID; }
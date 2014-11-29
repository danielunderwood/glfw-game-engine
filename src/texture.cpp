#include <stdio.h>

#include "SOIL.h"

#include "texture.h"

namespace GGE
{
    GLuint Texture::currentTexture = 0;

    Texture::Texture(const unsigned int * imageData)
    {
        // Generate a texture
        glGenTextures(1, &textureID);
        glBindTexture(textureType, textureID);

        // TODO: Make this work more generally
        glTexImage2D(textureType, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_INT, imageData);

        // Common initialization
        init();

        // Unbind texture
        glBindTexture(textureType, 0);
    }

    Texture::Texture(const char *filename, GLenum textureType) :
            textureType(textureType)
    {
        // Generate OpenGL texture
        glGenTextures(1, &textureID);
        glBindTexture(textureType, textureID);
        // Load Image
        printf("Loading %s as texture %d\n", filename, textureID);
        fflush(stdout);
        int height, width;
        unsigned char * texImage = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

        if (!texImage)
        {
            fprintf(stderr, "Texture %s failed to load!\n", filename);
            return;
        }

        // Assign Texture
        // TODO: Make this work with 1D and 3D textures
        glTexImage2D(textureType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);

        // Free Image Data
        SOIL_free_image_data(texImage);

        // Common initialization
        init();

        // Unbind texture
        // TODO: Check if this causes performance issues
        glBindTexture(textureType, 0);
    }

    Texture::~Texture()
    {
        // Delete textures
        glDeleteTextures(textureType, &textureID);
    }

    void Texture::init()
    {

        // Set Texture Parameters
        glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Generate Mipmaps
        glGenerateMipmap(textureType);
    }

    void Texture::bind()
    {
        currentTexture = textureID;
        glBindTexture(textureType, textureID);
        glActiveTexture(GL_TEXTURE0);
    }

    GLuint Texture::getTextureID()
    {
        return textureID;
    }
}
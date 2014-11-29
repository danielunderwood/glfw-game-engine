#pragma once

#include <glew.h>
#include <glfw3.h>

namespace GGE
{
// Represents a texture
    class Texture
    {
    public:
        // Already have image data (white/transparent)
        // Currently works for 1x1 pixel of color
        Texture(const unsigned int * imageData);

        // Load with soil
        Texture(const char *filename, GLenum textureType);

        ~Texture();

        // Plain and transparent textures
        // TODO: Implement these
        static Texture * WHITE;
        static Texture * TRANSPARENT;

        // Bind texture for use
        void bind();

        // Getter for textureID
        GLuint getTextureID();

    private:
        // Shared init function for constructors
        void init();

        // OpenGL's ID for the texture
        GLuint textureID;

        // Type identifier of texture
        GLenum textureType;

        // ID of Current Texture
        // TODO: Make this a texture object
        static GLuint currentTexture;
    };
}
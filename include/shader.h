#pragma once

#include <string>

#include "glew.h"
#include "glfw3.h"

// Class to represent an OpenGL Shader
class Shader
{
public:
    // Constructor to load from file
    Shader(const char * filename, GLenum shaderType);

    // Destructor
    ~Shader();

    // Getter for shaderID
    GLuint getShaderID();

private:
    // Text of shader
    std::string shaderString;

    // ID For shader
    GLuint shaderID;

    // Type of Shader
    GLenum shaderType;
};
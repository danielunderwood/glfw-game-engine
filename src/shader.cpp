#include <fstream>

#include "shader.h"

Shader::Shader(const char * filename, GLenum shaderType) :
    shaderType(shaderType)
{
    // TODO: Do this with logging class
    printf("Loading %s\n", filename);

    // Line buffer
    std::string line;

    // Stream for file
    std::ifstream shaderFileStream(filename);

    while(std::getline(shaderFileStream, line))
        shaderString += line + "\n"; // TODO: Stop from adding extra newlines here

    // Create OpenGL Shader
    shaderID = glCreateShader(shaderType);

    // TODO: Print Shader Logger Messages
    printf("Compiling %s\n", filename);

    // Set source for shader
    // TODO: Make this suck less
    const char * cShaderString = shaderString.c_str();
    glShaderSource(shaderID, 1, (GLchar const *const *) cShaderString, NULL);

    // Compile
    glCompileShader(shaderID);
}

Shader::~Shader()
{
    glDeleteShader(shaderID);
}

GLuint Shader::getShaderID() { return shaderID; }
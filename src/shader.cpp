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
    // TODO: Handle the case of file not existing
    std::ifstream shaderFileStream(filename);

    while(std::getline(shaderFileStream, line))
    {
        shaderString += line;

        // Add newline if not at end of file
        if(shaderFileStream.peek() != EOF) shaderString += '\n';
    }

    // Create OpenGL Shader
    shaderID = glCreateShader(shaderType);

    // TODO: Print Shader Logger Messages
    printf("Compiling %s\n", filename);

    // Set source for shader
    const GLchar * cShaderString = shaderString.c_str();
    glShaderSource(shaderID, 1, &cShaderString, NULL);

    // Compile
    glCompileShader(shaderID);
}

Shader::~Shader()
{
    glDeleteShader(shaderID);
}

GLuint Shader::getShaderID() { return shaderID; }
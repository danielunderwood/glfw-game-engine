#include <stdio.h>

#include "program.h"

// Initialize the currentProgram
GLuint Program::currentProgram = 0;

Program::Program(std::vector<Shader*> shaders) :
    shaders(shaders)
{
    // Create Program
    programID = glCreateProgram();
    printf("ProgramID: %d\n", programID);
    fflush(stdout);

    // Iterate through Shaders
    for(std::vector<Shader*>::iterator shader = shaders.begin(); shader != shaders.end(); shader++)
    {
        // Attach Shader
        glAttachShader(programID, (*shader)->getShaderID());
        printf("Shader %d attaching to Program %d\n", (*shader)->getShaderID(), programID);
    }
    fflush(stdout);

    // Link program
    glLinkProgram(programID);

    // Get link status
    GLint linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);

    // Resolve issues if linking failed
    if(linkStatus != GL_TRUE)
    {
        // Get length of log
        GLint logLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

        // Allocate storage for info log
        GLchar * linkerLog = new GLchar[logLength + 1];

        // Get linker log
        glGetProgramInfoLog(programID, logLength + 1, NULL, linkerLog);

        // Print message
        fprintf(stderr, "Program %d Linking Failed:\n%s\n", programID, linkerLog);

        // TODO: Figure out what to do when this fails
    }
}

Program::~Program()
{
    // Iterate through attached shaders
    for(std::vector<Shader*>::iterator shader = shaders.begin(); shader != shaders.end(); shader++)
    {
        // Detach Shader
        glDetachShader(programID, (*shader)->getShaderID());
    }

    // Delete program
    glDeleteProgram(programID);
}

GLuint Program::getProgramID() { return programID; }

GLuint Program::bind()
{
    // Set current program as this program
    // TODO: Make this thread-safe
    currentProgram = programID;

    // Tell OpenGL to use this program
    glUseProgram(programID);

    // Return the programID so we can chain
    return programID;
}

GLuint Program::unbind()
{
    // Set current program as 0
    currentProgram = 0;
    glUseProgram(currentProgram);

    // Return the current program for checking if there are thread issues
    // TODO: Find a way to make everything thread-safe
    return currentProgram;
}

GLuint Program::getCurrentProgram() { return currentProgram; }

GLuint Program::getUniform(const GLchar *uniformName)
{
    return glGetUniformLocation(programID, uniformName);
}

GLuint Program::getAttrib(const GLchar *attribName)
{
    return glGetAttribLocation(programID, attribName);
}

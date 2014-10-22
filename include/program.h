#pragma once

#include <vector>

#include "shader.h"

#include "glew.h"
#include "glfw3.h"

// Class representing OpenGL Program
// TODO: Implement getting attribute locations from shaders
class Program
{
public:
    // Constructor with vector of shaders
    Program(std::vector<Shader> shaders);

    // Destructor
    ~Program();

    // Getter for ProgramID
    // TODO: Change these types of getters just to getID?
    GLuint getProgramID();

    // Bind the program
    // TODO: Is this really necessary unless it starts needing more lines?
    GLuint bind();

    // Unbind program
    // TODO: See if there is a better way to do this
    GLuint unbind();

    // Get values from shaders
    GLuint getAttrib(const GLchar * attribName);
    GLuint getUniform(const GLchar * uniformName);

    // Get program currently being used by OpenGL
    static GLuint getCurrentProgram();

private:
    // ID of Program Currently Being Used
    static GLuint currentProgram;

    // ID of Program to OpenGL
    GLuint programID;

    // Shaders in program
    std::vector<Shader> shaders;

};
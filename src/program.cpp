#include <stdio.h>
#include <gtc/type_ptr.hpp>
#include <application.h>
#include <camera.h>

#include "program.h"

namespace GGE
{
    // Initialize the currentProgram
    Program *Program::currentProgram = NULL;

    // Initialize activePrograms
    std::list<Program *> Program::activePrograms;

    Program::Program(std::vector<Shader *> shaders) :
            shaders(shaders)
    {
        // Create Program
        programID = glCreateProgram();
        printf("ProgramID: %d\n", programID);
        fflush(stdout);

        // Iterate through Shaders
        for (std::vector<Shader *>::iterator shader = shaders.begin(); shader != shaders.end(); shader++)
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
        if (linkStatus != GL_TRUE)
        {
            // Get length of log
            GLint logLength;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

            // Allocate storage for info log
            GLchar *linkerLog = new GLchar[logLength + 1];

            // Get linker log
            glGetProgramInfoLog(programID, logLength + 1, NULL, linkerLog);

            // Print message
            fprintf(stderr, "Program %d Linking Failed:\n%s\n", programID, linkerLog);

            // TODO: Figure out what to do when this fails
            return;
        }

        // Add to list of active programs
        activePrograms.push_back(this);

        // Set up projection matrix
        bind();
        GLint uniProj = getUniform("projection");
        glUniformMatrix4fv(uniProj, 1, GL_FALSE,
                glm::value_ptr(Application::mainWindow->getProjectionMatrix()));
        unbind();
    }

    Program::~Program()
    {
        // Iterate through attached shaders
        for (std::vector<Shader *>::iterator shader = shaders.begin(); shader != shaders.end(); shader++)
        {
            // Detach Shader
            glDetachShader(programID, (*shader)->getShaderID());
        }

        // Delete program
        glDeleteProgram(programID);

        // Remove from active program list
        activePrograms.remove(this);
    }

    GLuint Program::getProgramID()
    {
        return programID;
    }

    GLuint Program::bind()
    {
        // Set current program as this program
        // TODO: Make this thread-safe
        currentProgram = this;

        // Tell OpenGL to use this program
        glUseProgram(programID);

        // Return the programID so we can chain
        return programID;
    }

    GLuint Program::unbind()
    {
        // Set current program as 0
        currentProgram = NULL;
        glUseProgram(0);

        // Return the current program for checking if there are thread issues
        // TODO: Find a way to make everything thread-safe
        return 0;
    }

    void Program::updateProjectionMatrix(glm::mat4 projectionMatrix)
    {
        for (std::list<Program *>::iterator program = activePrograms.begin();
             program != activePrograms.end(); program++)
        {
            (*program)->bind();
            GLint uniProj = (*program)->getUniform("projection");
            glUniformMatrix4fv(uniProj, 1, GL_FALSE,
                    glm::value_ptr(Application::mainWindow->getProjectionMatrix()));
            (*program)->unbind();
        }
    }

    void Program::updateViewMatrix(glm::mat4 viewMatrix)
    {
        for (std::list<Program *>::iterator program = activePrograms.begin();
             program != activePrograms.end(); program++)
        {
            (*program)->bind();
            GLint viewProj = (*program)->getUniform("view");
            glUniformMatrix4fv(viewProj, 1, GL_FALSE,
                    glm::value_ptr(Camera::getCurrentCamera()->getViewMatrix()));
            (*program)->unbind();
        }
    }

    Program *Program::getCurrentProgram()
    {
        return currentProgram;
    }

    GLuint Program::getUniform(const GLchar *uniformName)
    {
        return glGetUniformLocation(programID, uniformName);
    }

    GLuint Program::getAttrib(const GLchar *attribName)
    {
        return glGetAttribLocation(programID, attribName);
    }
}
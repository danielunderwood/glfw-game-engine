#include "window.h"
#include <iostream>
#include <stdio.h>
#include <shader.h>
#include <program.h>
#include <mesh.h>
#include <stdlib.h>
#include <application.h>
#include <gtc/matrix_transform.hpp>

std::list<Window*> Window::windows;

Window::Window(int height, int width, bool fullscreen, char * title) :
	height(height),
	width(width),
	fullscreen(fullscreen),
	title(title),
    shouldClose(false)
{
    // Initialiize with glfw
	init();

    // Put in windows list
    windows.push_back(this);

    // Make perspective matrix
    // TODO: Dynamic FOV and Near/Far
    projectionMatrix = glm::perspective(90.0f, float(width/height), 1.0f, 100.0f);
    printf("Projection Matrix: %f, %f, %f, %f\n"
            "                   %f, %f, %f, %f\n"
            "                   %f, %f, %f, %f\n"
            "                   %f, %f, %f, %f\n",
    projectionMatrix[0][0], projectionMatrix[0][1], projectionMatrix[0][2], projectionMatrix[0][3],
    projectionMatrix[1][0], projectionMatrix[1][1], projectionMatrix[1][2], projectionMatrix[1][3],
    projectionMatrix[2][0], projectionMatrix[2][1], projectionMatrix[2][2], projectionMatrix[2][3],
    projectionMatrix[3][0], projectionMatrix[3][1], projectionMatrix[3][2], projectionMatrix[3][3]);
}

Window::~Window()
{
    // Destroy window in GLFW
    glfwDestroyWindow(window);

    // Remove from list of windows
    windows.remove(this);

}

void Window::setRenderFunction(RenderFunction renderFunction)
{
    this->renderFunction = renderFunction;
}

GLFWwindow * Window::getGLFWWindow() { return window; }
int Window::getHeight() { return height; }
int Window::getWidth() { return width; }
bool Window::isFullscreen() { return fullscreen; }
bool Window::isClosed() { return shouldClose; }


void Window::init()
{
    
    // Make GLFW Window
    // TODO: Control which monitor it goes to and figure out last parameter
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    // Check that Window opened
    if(!window)
    {
        fprintf(stderr, "ERROR: GLFW Could Not Open Window"); // TODO: Print this to log file
        glfwTerminate();
        return; // TODO: Return error instead of nothing
    }
    
    // Make the current context be the window that was just created
    glfwMakeContextCurrent(window);

    // Set callback for changing window size
    glfwSetWindowSizeCallback(window, resizeCallback);

    // Set clear color
    // TODO: Move this to somewhere that can be changed when needed
    glClearColor(1.0, 0.0, 0.0, 1.0);

    // Initialize glew if not initialized
    if(!Application::glewInitialized)
    {
        // Initialize GLEW
        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK)
        {
            fprintf(stderr, "GLEW Failed To Initialize. Exiting...\n");
            exit(1);
        }
        // Print Renderer info
        // TODO: Use logger class
        const GLubyte * renderer = glGetString(GL_RENDERER);
        const GLubyte * version = glGetString(GL_VERSION);

        printf("Renderer: %s\n", renderer);
        printf("OpenGL Version: %s\n", version);
        fflush(stdout);

        Application::glewInitialized = true;
    }
}

void Window::resizeCallback(GLFWwindow * window, int newWidth, int newHeight)
{
    // Change glViewport to new window size
    glViewport(0, 0, newWidth, newHeight);

    // Update Perspective Matrix
    // TODO: Dynamic FOV and Near/Far
    // TODO: Do this in a less hacky way
    for(std::list<Window*>::iterator w = windows.begin(); w != windows.end(); w++)
    {
        if ((*w)->window == window)
        {
            // Set the perspective matrix of this window
            (*w)->projectionMatrix = glm::perspective(90.0f, float(newWidth / newHeight), 0.0f, 100.0f);

            // Update shaders
            Program::updateProjectionMatrix((*w)->projectionMatrix);

            printf("Projection Matrix: %f, %f, %f, %f\n"
                            "                   %f, %f, %f, %f\n"
                            "                   %f, %f, %f, %f\n"
                            "                   %f, %f, %f, %f\n",
                    (*w)->projectionMatrix[0][0], (*w)->projectionMatrix[0][1], (*w)->projectionMatrix[0][2], (*w)->projectionMatrix[0][3],
                    (*w)->projectionMatrix[1][0], (*w)->projectionMatrix[1][1], (*w)->projectionMatrix[1][2], (*w)->projectionMatrix[1][3],
                    (*w)->projectionMatrix[2][0], (*w)->projectionMatrix[2][1], (*w)->projectionMatrix[2][2], (*w)->projectionMatrix[2][3],
                    (*w)->projectionMatrix[3][0], (*w)->projectionMatrix[3][1], (*w)->projectionMatrix[3][2], (*w)->projectionMatrix[3][3]);

            break;
        }
    }
}

bool Window::renderFrame()
{
    // Clear Screen
    // TODO: Add clearing depth buffer when it is necessary
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Call assigned render function
    renderFunction();

    // Poll inputs
    glfwPollEvents();

    // Swap Buffers -- Always do this at the end of frame's render
    glfwSwapBuffers(window);

    // Determine if window should close
    // TODO: Move key functionality to input callback
    bool shouldClose = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window);

    return !shouldClose;
}

glm::mat4 Window::getProjectionMatrix() { return projectionMatrix; }

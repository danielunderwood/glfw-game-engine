#include "window.h"
#include <iostream>
#include <stdio.h>

Window::Window(int height, int width, bool fullscreen, char * title) :
	height(height),
	width(width),
	fullscreen(fullscreen),
	title(title),
    shouldClose(false)
{
	init();
}

Window::~Window()
{
    glfwDestroyWindow(window);
}

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
    
    return; // TODO: Return Success Message at this point instead of nothing
}

void Window::resizeCallback(GLFWwindow * window, int newWidth, int newHeight)
{
    // Change glViewport to new window size
    glViewport(0, 0, newWidth, newHeight);
}

bool Window::renderFrame()
{
    // Clear Screen
    // TODO: Add clearing depth buffer when it is necessary
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap Buffers -- Always do this at the end of frame's render
    glfwSwapBuffers(window);

    // Poll inputs
    glfwPollEvents();

    // Determine if window should close
    // TODO: Move key functionality to input callback
    shouldClose = shouldClose || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window);

    return !shouldClose;
}

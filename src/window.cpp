#include "window.h"
#include <iostream>
#include <stdio.h>
#include <shader.h>
#include <program.h>
#include <triangle.h>
#include <stdlib.h>

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

// Put this here for biscuits
// Global stuff for testing
Program * p;
Triangle * t1;
Triangle * t2;
Triangle * t3;

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

    // Initialize GLEW
    // TODO: Put this somewhere
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        exit(1);

    // Set clear color
    // TODO: Move this to somewhere that can be changed when needed
    glClearColor(1.0, 0.0, 0.0, 1.0);

    // Load shaders
    // TODO: This doesn't go here!
    Shader * vs = new Shader("res/shaders/basicShader.vs", GL_VERTEX_SHADER);
    Shader * fs = new Shader("res/shaders/basicShader.fs", GL_FRAGMENT_SHADER);
    std::vector<Shader> v;
    v.push_back(*vs);
    v.push_back(*fs);
    p = new Program(v);
    std::vector<GLfloat> points;
    points.push_back(-0.5);
    points.push_back(-0.5);
    points.push_back(0);
    points.push_back(0);
    points.push_back(0.5);
    points.push_back(0);
    points.push_back(0.5);
    points.push_back(-0.5);
    points.push_back(0);
    t1 = new Triangle(points);

    // Tryna make a square?
    // Note: This DOESN"T make a square
    std::vector<GLfloat> points2;
    // First Triangle
    points2.push_back(-0.5);
    points2.push_back(-0.5);
    points2.push_back(0);
    points2.push_back(0);
    points2.push_back(0.5);
    points2.push_back(0);
    points2.push_back(0.5);
    points2.push_back(-0.5);
    points2.push_back(0);
    // Second triangle
    points2.push_back(-1.0);
    points2.push_back(-1.0);
    points2.push_back(0.0);
    points2.push_back(-1.0);
    points2.push_back(1.0);
    points2.push_back(0.0);
    points2.push_back(0.0);
    points2.push_back(1.0);
    points2.push_back(0.0);
    t2 = new Triangle(points2);

    // Let's try another
    std::vector<GLfloat> points3;
    points3.push_back(-0.5);
    points3.push_back(0.5);
    points3.push_back(0);
    points3.push_back(0);
    points3.push_back(0.5);
    points3.push_back(0);
    points3.push_back(-0.5);
    points3.push_back(-0.5);
    points3.push_back(0);
    t3 = new Triangle(points3);

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

    p->bind();
    //t1->draw();
    t2->draw();
    //t3->draw();
    p->unbind();

    // Poll inputs
    glfwPollEvents();

    // Swap Buffers -- Always do this at the end of frame's render
    glfwSwapBuffers(window);

    // Determine if window should close
    // TODO: Move key functionality to input callback
    shouldClose = shouldClose || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window);

    return !shouldClose;
}

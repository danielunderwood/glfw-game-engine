#include "window.h"
#include <iostream>
#include <stdio.h>
#include <shader.h>
#include <program.h>
#include <mesh.h>
#include <stdlib.h>
#include <application.h>

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
Mesh * t1;
Mesh * t2;
Mesh * t3;
Mesh * square;

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
    t1 = new Mesh(points);

    // Tryna make a square?
    // Note: This DOESN'T make a square
    std::vector<GLfloat> points2;
    // First Mesh
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
    t2 = new Mesh(points2);

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
    t3 = new Mesh(points3);

    // Test drawing with fans
    std::vector<GLfloat> squarePts;
    squarePts.push_back(-0.5);
    squarePts.push_back(0.5);
    squarePts.push_back(0.0);
    squarePts.push_back(0.5);
    squarePts.push_back(0.5);
    squarePts.push_back(0.0);
    squarePts.push_back(0.5);
    squarePts.push_back(-0.5);
    squarePts.push_back(0.0);
    squarePts.push_back(-0.5);
    squarePts.push_back(-0.5);
    squarePts.push_back(0.0);

    square = new Mesh(squarePts, GL_STATIC_DRAW, GL_TRIANGLE_FAN);

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
    //t2->draw();
    //t3->draw();
    square->draw();
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

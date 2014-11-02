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
Program * texP;
Texture * brickTex;
Mesh * t1, * t2, * t3, * square, * texturedTriangle;

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
    std::vector<Shader *> shaders;
    shaders.push_back(vs);
    shaders.push_back(fs);
    p = new Program(shaders);

    // Make texture program
    Shader * texvs = new Shader("res/shaders/textureShader.vs", GL_VERTEX_SHADER);
    Shader * texfs = new Shader("res/shaders/textureShader.fs", GL_FRAGMENT_SHADER);
    std::vector<Shader*> texShaders;
    texShaders.push_back(texvs);
    texShaders.push_back(texfs);
    texP = new Program(texShaders);

    // Brick Texture
    brickTex = new Texture("res/textures/fabric-pattern.jpg");

    std::vector<GLfloat> points;
    std::vector<GLfloat> tex;
    points.push_back(-0.5);
    points.push_back(-0.5);
    points.push_back(0);
    points.push_back(0);
    points.push_back(0.5);
    points.push_back(0);
    points.push_back(0.5);
    points.push_back(-0.5);
    points.push_back(0);
    t1 = new Mesh(points, tex, NULL);

    // Tryna make a square?
    // Note: This DOESN'T make a square
    std::vector<GLfloat> points2;
    std::vector<GLfloat> tex2;
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
    t2 = new Mesh(points2, tex2, NULL);

    // Let's try another
    std::vector<GLfloat> points3;
    std::vector<GLfloat> tex3;
    points3.push_back(-0.5);
    points3.push_back(0.5);
    points3.push_back(0);
    points3.push_back(0);
    points3.push_back(0.5);
    points3.push_back(0);
    points3.push_back(-0.5);
    points3.push_back(-0.5);
    points3.push_back(0);
    t3 = new Mesh(points3, tex3, NULL);

    // Test drawing with strips
    std::vector<GLfloat> squarePts;
    std::vector<GLfloat> squareTex;
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

    squareTex.push_back(1.0);
    squareTex.push_back(0.0);
    squareTex.push_back(0.0);
    squareTex.push_back(1.0);
    squareTex.push_back(1.0);
    squareTex.push_back(1.0);
    squareTex.push_back(1.0);
    squareTex.push_back(0.0);

    square = new Mesh(squarePts, squareTex, brickTex, GL_STATIC_DRAW, GL_TRIANGLE_FAN);

    // Test textured triangle
    std::vector<GLfloat> ttPoints;
    std::vector<GLfloat> ttTex;

    ttPoints.push_back(-0.5);
    ttPoints.push_back(-0.5);
    ttPoints.push_back(0.0);
    ttPoints.push_back(0.0);
    ttPoints.push_back(0.5);
    ttPoints.push_back(0.0);
    ttPoints.push_back(0.5);
    ttPoints.push_back(-0.5);
    ttPoints.push_back(0.0);

    ttTex.push_back(0.0);
    ttTex.push_back(1.0);
    ttTex.push_back(0.5);
    ttTex.push_back(0.0);
    ttTex.push_back(1.0);
    ttTex.push_back(1.0);

    texturedTriangle = new Mesh(ttPoints, ttTex, brickTex);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    p->bind();
    //t1->draw();
    //t2->draw();
    //t3->draw();
    p->unbind();

    texP->bind();
    brickTex->bind();
    //square->draw();
    texturedTriangle->draw();
    texP->unbind();

    // Poll inputs
    glfwPollEvents();

    // Swap Buffers -- Always do this at the end of frame's render
    glfwSwapBuffers(window);

    // Determine if window should close
    // TODO: Move key functionality to input callback
    shouldClose = shouldClose || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window);

    return !shouldClose;
}

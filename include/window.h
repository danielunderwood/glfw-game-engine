#pragma once

#include "glew.h"
#include "glfw3.h"

// Represents a GLFW Window with context
class Window
{
public:
	// Constructor
	Window(int height, int width, bool fullscreen, char * title);
	//Destructor
	~Window();

    // Set the function for the rendering in this window
    void setRenderFunction(bool (*renderFunction)());

	// Getters
    GLFWwindow * getGLFWWindow();
	int getHeight();
	int getWidth();
	bool isFullscreen();
	bool isClosed();

    // Renders one frame and returns false when it should close
    // TODO: Figure out the proper place to put closing logic
    // TODO: Abstract this so we can declare a function to render with (function pointer)
    bool renderFrame();
private:
	int height;			// Height of window
	int width;			// Width of window
	bool fullscreen;		// Is window fullscreen?
	bool shouldClose;		// Should window close?
	char * title;			// Title of window
	GLFWwindow * window;	// Window for GLFW

    // Pointer to function to render with
    bool (*renderFunction)();

	// Initializes window with GLFW
	void init();

    // Callback registered with GLFW in init() to change the glViewport to match the new window size
    // TODO: Figure out if this needs to remain static or what should be done
    static void resizeCallback(GLFWwindow * window, int newWidth, int newHeight);
};
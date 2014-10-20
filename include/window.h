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

	// Getters
	int getHeight();
	int getWidth();
	bool isFullscreen();
	bool isClosed();
private:
	int height;			// Height of window
	int width;			// Width of window
	bool fullscreen;		// Is window fullscreen?
	bool shouldClose;		// Should window close?
	char * title;			// Title of window
	GLFWwindow * window;	// Window for GLFW

	// Initializes window with GLFW
	void init();

    // Callback registered with GLFW in init() to change the glViewport to match the new window size
    // TODO: Figure out if this needs to remain static or what should be done
    static void resizeCallback(GLFWwindow * window, int newWidth, int newHeight);
};
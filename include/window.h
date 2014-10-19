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
};
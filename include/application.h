#pragma once

#include "glew.h"
#include "glfw3.h"

#include "window.h"

// Class representing an application
// Should implement singleton pattern
class Application
{
public:
	// Constructor
	Application();
	// Destructor
	~Application();

	// Add a window to application and open
	// TODO: Add option for this window not to be focused
	void addWindow(int height, int width, bool fullscreen, char * title, bool isMain);

private:
	// Internal Error Codes
    enum ErrorCode { GLFW_INIT_FAILURE, GLEW_INIT_FAILURE, CREATE_WINDOW_FAILURE, SUCCESS };
	
	// Windows belonging to application
	Window * windows;
	Window * mainWindow;

	// Initializes application
	int init();

	// Terminates application
	void terminate(ErrorCode e);
};
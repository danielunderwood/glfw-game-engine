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
	Window * addWindow(int height, int width, bool fullscreen, char * title, bool isMain);

    // Start rendering the application
    // TODO: Figure out if this is where starting to render really needs to be
    // Windows belonging to application
    // TODO: Make a function or something to render for the application so we aren't accessing these
    // windows directly
    Window * windows;
    static Window * mainWindow;

    // Callback to set for GLFW error
    // TODO: Move this to a logging class
    static void glfwErrorCallback(int error, const char * description);

    // Flag if GLEW initialized
    // Static since Application should be singleton
    static bool glewInitialized;


private:
	// Internal Error Codes
    enum ErrorCode { GLFW_INIT_FAILURE, GLEW_INIT_FAILURE, CREATE_WINDOW_FAILURE, SUCCESS };

	// Initializes application
	int init();

	// Terminates application
	void terminate(ErrorCode e);
};
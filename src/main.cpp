#include <stdio.h>
#include "application.h"

int main(int argc, char ** argv)
{
    // Start Application
    Application * app = new Application();

    // Add Window
    app->addWindow(320, 620, true, "Test", true);

    // Render Loop
    while(app->mainWindow->renderFrame());

    // Destroy application
    delete app;

    return 0;
}

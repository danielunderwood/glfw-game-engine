#include <stdio.h>
#include "application.h"

int main(int argc, char ** argv)
{
    // Open Window
    Application * app = new Application();
    app->addWindow(320, 620, true, "Test", true);
    // TODO: Figure out what is happening here
    while(app->mainWindow->renderFrame()) {}
    return 0;
}

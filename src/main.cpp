#include "application.h"

int main(int argc, char ** argv)
{
    // Open Window
    Application * app = new Application();
    app->addWindow(320, 620, true, "Test", true);
    return 0;
}

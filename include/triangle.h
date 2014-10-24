#pragma once

#include <vector>

#include "glew.h"
#include "glfw3.h"

class Triangle
{
public:
    // Constructor
    // TODO: Figure out what the best way to pass draw type is
    Triangle(GLfloat points[3], GLenum drawType = GL_STATIC_DRAW);
    // Destructor
    ~Triangle();

    // Draw Triangle
    void draw();

private:
    // Points in triangle
    // TODO: See if there is something better to use for these
    GLfloat points[3];

    // Draw type
    GLenum drawType;
};
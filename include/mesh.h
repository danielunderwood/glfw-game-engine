#pragma once

#include <vector>

#include "glew.h"
#include "glfw3.h"

class Mesh
{
public:
    // Constructor
    // TODO: Figure out what the best way to pass draw type is
    Mesh(std::vector<GLfloat> points, GLenum drawType = GL_STATIC_DRAW, GLenum drawShape = GL_TRIANGLES);
    // Destructor
    ~Mesh();

    // Draw Triangle
    void draw();

private:
    // Points in triangle
    // TODO: See if there is something better to use for these
    std::vector<GLfloat> points;

    // vao object for mesh
    GLuint vao;

    // Draw type (static, dynamic, etc.)
    GLenum drawType;
    // Shape to draw (triangle, triangle strips, etc.)
    GLenum drawShape;
};
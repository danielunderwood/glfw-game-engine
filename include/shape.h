#pragma once

#include <vector>

#include "glew.h"
#include "glfw3.h"

#include "material.h"

namespace GGE
{
    // A set of coordinates for a shape consisting of position, normals, and texture coordinates
    typedef struct CoordinateSet
    {
        std::vector<GLfloat> positionCoordinates, normals, textureCoordinates;
        CoordinateSet() : positionCoordinates(std::vector<GLfloat>()),
                          normals(std::vector<GLfloat>()),
                          textureCoordinates(std::vector<GLfloat>())
        {};
    } CoordinateSet;

    // Class to represent shape to be drawn
    // A collection of these make a mesh
    class Shape
    {
    public:
        // Constructor
        Shape(CoordinateSet * coordinates, Material * material);
        // Destructor
        ~Shape();

        // Draw this shape
        void draw();

    private:
        // Shape properties
        CoordinateSet * coordinates;

        // Material for this shape
        // TODO: Move to shape/material map in mesh?
        Material * material;
    };
}
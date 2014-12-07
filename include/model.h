#pragma once

#include <list>

#include "shape.h"
#include "material.h"

namespace GGE {
// Class to represent an in-game model (textured mesh)
    class Model {
    public:
        // Constructor to load from file
        Model(const char * filename, const char * directory);
        // Constructor with model and material
        Model(std::list<Shape*> shapes);

        // Destructor
        ~Model();

        // Draw the model
        void draw();

    private:
        // Shapes that make up model
    std::list<Shape *> shapes;
    };
}
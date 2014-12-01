#pragma once

#include "mesh.h"
#include "material.h"

namespace GGE {
// Class to represent an in-game model (textured mesh)
    class Model {
    public:
        // Constructor to load from file
        Model(const char * filename, const char * directory);
        // Constructor with model and material
        Model(Mesh * mesh, Material * material);

        // Destructor
        ~Model();

        // Draw the model
        void draw();

    private:
        // Mesh for model
        Mesh * mesh;
        // Material for model
        // TODO: Make compatible for multiple materials on a model
        Material * material;
    };
}
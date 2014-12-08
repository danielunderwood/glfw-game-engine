#include "tiny_obj_loader.h"

#include "model.h"

namespace GGE
{
    Model::Model(const char * filename, const char * directory)
    {
        // Vector for shapes
        std::vector<tinyobj::shape_t> shapes;

        // Vector for material support
        // TODO: Integrate material support with rest of program
        std::vector<tinyobj::material_t> materials;

        printf("Loading %s...\n", filename, directory);
        fflush(stdout);

        std::string error = tinyobj::LoadObj(shapes, materials, filename);

        // Print error message
        if(!error.empty())
        {
            fprintf(stderr, "Error Loading %s: %s\n", filename, error.c_str());
            return;
        }

        printf("Loaded %d shapes and %d materials from %s\n", shapes.size(), materials.size(), filename);
        fflush(stdout);

        std::vector<GLfloat> meshPoints;

        // Iterate through shapes
        for(int shape = 0; shape < shapes.size(); shape++)
        {
            // Assign vertex values to mesh
            for (int vertex = 0; vertex < shapes[shape].mesh.positions.size() / 3; vertex++)
            {
                // TODO: Figure out how to do this in a better way
                meshPoints.push_back(shapes[shape].mesh.positions[3 * vertex + 0]);
                meshPoints.push_back(shapes[shape].mesh.positions[3 * vertex + 1]);
                meshPoints.push_back(shapes[shape].mesh.positions[3 * vertex + 2]);
            }
        }

        for (size_t i = 0; i < materials.size(); i++) {
            printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
            printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
            printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
            printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
            printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
            printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
            printf("  material.Ns = %f\n", materials[i].shininess);
            printf("  material.Ni = %f\n", materials[i].ior);
            printf("  material.dissolve = %f\n", materials[i].dissolve);
            printf("  material.illum = %d\n", materials[i].illum);
            printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
            printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
            printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
            printf("  material.map_Ns = %s\n", materials[i].normal_texname.c_str());
            std::map<std::string, std::string>::const_iterator it(materials[i].unknown_parameter.begin());
            std::map<std::string, std::string>::const_iterator itEnd(materials[i].unknown_parameter.end());
            for (; it != itEnd; it++) {
                printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
            }
        }
        fflush(stdout);
    }
    Model::Model(std::list<Shape*> shapes) :
        shapes(shapes)
    {
    }

    Model::~Model(){}
}
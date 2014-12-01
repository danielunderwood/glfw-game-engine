#include <stdio.h>

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include "tiny_obj_loader.h"

#include "application.h"
#include "program.h"
#include "mesh.h"

namespace GGE
{
    Mesh::Mesh(std::vector<GLfloat> points, std::vector<GLfloat> textureCoords,
            Texture * texture, Program *  program, GLenum drawType, GLenum drawShape) :
            points(points),
            textureCoords(textureCoords),
            texture(texture),
            program(program),
            drawType(drawType),
            drawShape(drawShape)
    {
        init();
    }

    Mesh::Mesh(std::vector<GLfloat> points) :
            points(points)
    {
        init();
    }

    Mesh::Mesh(const char * filename, const char * directory, Program * program) :
    program(program),
    drawType(GL_STATIC_DRAW),
    drawShape(GL_TRIANGLE_STRIP)
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

        // Coordinate sets
        // TODO: Find a better way to do this
        std::vector<CoordinateSet *> coordinateSets;
        // Material ID to use for each shape
        std::vector< std::vector<int> > materialIDs;

        // Iterate through shapes
        for(int shape = 0; shape < shapes.size(); shape++)
        {
            // CoordinateSet for this shape
            CoordinateSet * cs = new CoordinateSet();

            for (int vertex = 0; vertex < shapes[shape].mesh.positions.size() / 3; vertex++)
            {
                // Keep track of current mesh to make following calls easier
                tinyobj::mesh_t currentMesh = shapes[shape].mesh;

                // Make new vertex every 3 vertices
                for(int i = 0; i < 3; i++)
                {
                    if(!currentMesh.positions.empty())
                        cs->positionCoordinates.push_back(currentMesh.positions[3 * vertex + i]);

                    // TODO: Clean this up if normals are not declared in file
                    if(!currentMesh.normals.empty())
                        cs->normals.push_back(currentMesh.normals[3 * vertex + i]);

                    // Cycle through texture coordinates every two points
                    // TODO: Clean this up if texture coordinates are not declared
                    if(i < 3 && !currentMesh.normals.empty())
                        cs->textureCoordinates.push_back(currentMesh.texcoords[2 * vertex + i]);

                    points.push_back(currentMesh.positions[3 * vertex + i]);
                }
                // TODO: Figure out how to do this in a better way

            }

            // Add this coordinate set to vector
            coordinateSets.push_back(cs);

            // Add material ID for this shape
            materialIDs.push_back(shapes[shape].mesh.material_ids);
        }

        // Materials from file
        std::vector<Material *> mats;

        // Iterate through materials
        for (int material = 0; material < materials.size(); material++)
        {
            // Current material for simpler code
            tinyobj::material_t currentMaterial = materials[material];

            // Assign array properties
            // TODO: Use uniform or some type of cast

            LightingProperties * lp = new LightingProperties();
            TextureSet * ts = new TextureSet();

            // Assign RGB values
            for(int i = 0; i < 3; i++)
            {
                lp->ambientColor[i] = currentMaterial.ambient[i];
                lp->diffuseColor[i] = currentMaterial.diffuse[i];
                lp->specularColor[i] = currentMaterial.specular[i];
                lp->transmissionColor[i] = currentMaterial.transmittance[i];
                lp->emissionColor[i] = currentMaterial.emission[i];
            }

            // Assign float values
            lp->shininess = currentMaterial.shininess;
            lp->indexOfRefraction = currentMaterial.ior;
            lp->dissolve = currentMaterial.dissolve;

            // Map textures
            // TODO: Generalize texture types - Probably done in Texture constructor
            if(!currentMaterial.ambient_texname.empty())
                ts->ambientTexture = new Texture(currentMaterial.ambient_texname.c_str(), GL_TEXTURE_2D);
            if(!currentMaterial.diffuse_texname.empty())
                ts->diffuseTexture = new Texture(currentMaterial.diffuse_texname.c_str(), GL_TEXTURE_2D);
            if(!currentMaterial.specular_texname.empty())
                ts->specularTexture = new Texture(currentMaterial.specular_texname.c_str(), GL_TEXTURE_2D);
            if(!currentMaterial.normal_texname.empty())
                ts->normalTexture = new Texture(currentMaterial.normal_texname.c_str(), GL_TEXTURE_2D);

            // Add new material
            // TODO: Make this work with texture
            mats.push_back(new Material(NULL, lp));
        }

        init();
    }

    Mesh::~Mesh()
    {
    //TODO: Delete vbos and vaos
    }

    void Mesh::init()
    {
        // Standard initialization
        // TODO: Move this to common function

        // Bind program
        program->bind();

        // Make a VBO to hold points
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points[0], drawType);

        // VBO TO hold colors
        GLuint colorVbo = 0;
        glGenBuffers(1, &colorVbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorVbo);

        // Make a VAO for the points VBO
        // TODO: Get indices from shaders
        vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Color if no texture coordinates
        // TODO: Remove this and find a better way of testing
        if (textureCoords.empty())
        {
            static const float colors[] = {
                    1.0, 1.0, 1.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 1.0
            };

            // Assign data to vbo
            glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
            // Describe data in vao
            GLuint colorIndex = program->getAttrib("color");
            glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(colorIndex);
        }
        else
        {
            // Assign data to vbo
            glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(GLfloat), &textureCoords[0], drawType);
            // Describe data in vao
            GLuint texCoordIndex = program->getAttrib("texCoord");
            glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(texCoordIndex);
        }

        // Points
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        GLuint positionIndex = program->getAttrib("position");
        glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(positionIndex);

        // Upload model matrix
        GLint uniModel = program->getUniform("model");
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        // Unbind program
        program->unbind();
    }

    void Mesh::draw()
    {
        // Bind program
        program->bind();
        // Bind vao
        glBindVertexArray(vao);
        // TODO: Bind texture here

        // Draw Mesh
        glDrawArrays(drawShape, 0, points.size());

        // TODO: See if unbinding is costly
        // Unbind vao
        glBindVertexArray(0);
        // Unbind program
        program->unbind();
    }

    glm::vec3 Mesh::move(glm::vec3 translation)
    {
        int dims = modelMatrix.length() - 1;
        // Apply translation
        for (int i = 0; i < dims; i++)
            modelMatrix[dims][i] += translation[i];

        // Upload new model matrix
        // TODO: Figure out about binding/unbinding program here
        program->bind();
        GLint uniModel = program->getUniform("model");
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        program->unbind();

        return Entity::move(translation);
    }

    glm::vec3 Mesh::setPosition(glm::vec3 newPosition)
    {
        // Set new position
        int dims = modelMatrix.length() - 1;
        for (int i = 0; i < dims; i++)
            modelMatrix[dims][i] = newPosition[i];

        // Upload new model matrix
        program->bind();
        GLint uniModel = program->getUniform("model");
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        program->unbind();

        return Entity::setPosition(newPosition);
    }

    glm::mat4 Mesh::getModelMatrix()
    {
        return modelMatrix;
    }
}
#include "program.h"
#include "mesh.h"

Mesh::Mesh(std::vector<GLfloat> points, std::vector<GLfloat> textureCoords,
        Texture * texture, GLenum drawType, GLenum drawShape) :
    points(points),
    textureCoords(textureCoords),
    texture(texture),
    drawType(drawType),
    drawShape(drawShape)
{
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
    if(textureCoords.empty())
    {
        static const float colors[] = {
                1.0, 1.0, 1.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0
        };

        // Assign data to vbo
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        // Describe data in vao
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
    else
    {
        // Assign data to vbo
        glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(GLfloat), &textureCoords[0], drawType);
        // Describe data in vao
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    }

    // Points
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);   // Points
    glEnableVertexAttribArray(1);   // Colors
}

Mesh::~Mesh()
{
//TODO: Delete vbos and vaos
}

void Mesh::draw()
{
    // Bind vao
    glBindVertexArray(vao);
    // Draw Mesh
    glDrawArrays(drawShape, 0, points.size());
    // Unbind vao
    glBindVertexArray(0);
}

#include <program.h>
#include "mesh.h"

Mesh::Mesh(std::vector<GLfloat> points, GLenum drawType, GLenum drawShape) :
    points(points),
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

    float colors[] = {
            1.0, 1.0, 1.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Make a VAO for the points VBO
    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Points
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

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

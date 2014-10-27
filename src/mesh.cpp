#include "mesh.h"

Mesh::Mesh(std::vector<GLfloat> points, GLenum drawType) :
    points(points)
{
}

Mesh::~Mesh(){}

// TODO: Move most of this logic to constructor?
void Mesh::draw()
{
    // Make a VBO to hold points
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points[0], GL_STATIC_DRAW);

    // Make a VAO for the points VBO
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Draw Mesh
    glDrawArrays(GL_TRIANGLES, 0, points.size()/2);
}

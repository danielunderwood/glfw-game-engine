#include <vector>
#include <stdio.h>

#include "application.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "program.h"


Application * app;

// Put this here for biscuits
// Global stuff for testing
Program * p;
Program * texP;
Texture * brickTex;
Mesh * t1, * t2, * t3, * square, * texturedTriangle;
void setupScene()
{
    // Set clear color
    // TODO: Move this to somewhere that can be changed when needed
    glClearColor(1.0, 0.0, 0.0, 1.0);

    // Load shaders
    // TODO: This doesn't go here!
    Shader * vs = new Shader("res/shaders/basicShader.vs", GL_VERTEX_SHADER);
    Shader * fs = new Shader("res/shaders/basicShader.fs", GL_FRAGMENT_SHADER);
    std::vector<Shader *> shaders;
    shaders.push_back(vs);
    shaders.push_back(fs);
    p = new Program(shaders);

    // Make texture program
    Shader * texvs = new Shader("res/shaders/textureShader.vs", GL_VERTEX_SHADER);
    Shader * texfs = new Shader("res/shaders/textureShader.fs", GL_FRAGMENT_SHADER);
    std::vector<Shader*> texShaders;
    texShaders.push_back(texvs);
    texShaders.push_back(texfs);
    texP = new Program(texShaders);

    // Brick Texture
    brickTex = new Texture("res/textures/texture-brick.png");

    std::vector<GLfloat> points;
    std::vector<GLfloat> tex;
    points.push_back(-0.5);
    points.push_back(-0.5);
    points.push_back(0);
    points.push_back(0);
    points.push_back(0.5);
    points.push_back(0);
    points.push_back(0.5);
    points.push_back(-0.5);
    points.push_back(0);

    t1 = new Mesh(points, tex, NULL, p);

    // Tryna make a square?
    // Note: This DOESN'T make a square
    std::vector<GLfloat> points2;
    std::vector<GLfloat> tex2;
    // First Mesh
    points2.push_back(-0.5);
    points2.push_back(-0.5);
    points2.push_back(0);
    points2.push_back(0);
    points2.push_back(0.5);
    points2.push_back(0);
    points2.push_back(0.5);
    points2.push_back(-0.5);
    points2.push_back(0);
    // Second triangle
    points2.push_back(-1.0);
    points2.push_back(-1.0);
    points2.push_back(0.0);
    points2.push_back(-1.0);
    points2.push_back(1.0);
    points2.push_back(0.0);
    points2.push_back(0.0);
    points2.push_back(1.0);
    points2.push_back(0.0);

    t2 = new Mesh(points2, tex2, NULL, p);

    // Let's try another
    std::vector<GLfloat> points3;
    std::vector<GLfloat> tex3;
    points3.push_back(-0.5);
    points3.push_back(0.5);
    points3.push_back(0);
    points3.push_back(0);
    points3.push_back(0.5);
    points3.push_back(0);
    points3.push_back(-0.5);
    points3.push_back(-0.5);
    points3.push_back(0);

    t3 = new Mesh(points3, tex3, NULL, p);

    // Test drawing with strips
    std::vector<GLfloat> squarePts;
    std::vector<GLfloat> squareTex;
    squarePts.push_back(-0.5);
    squarePts.push_back(0.5);
    squarePts.push_back(0.0);
    squarePts.push_back(0.5);
    squarePts.push_back(0.5);
    squarePts.push_back(0.0);
    squarePts.push_back(0.5);
    squarePts.push_back(-0.5);
    squarePts.push_back(0.0);
    squarePts.push_back(-0.5);
    squarePts.push_back(-0.5);
    squarePts.push_back(0.0);

    squareTex.push_back(1.0);
    squareTex.push_back(0.0);
    squareTex.push_back(0.0);
    squareTex.push_back(1.0);
    squareTex.push_back(1.0);
    squareTex.push_back(1.0);
    squareTex.push_back(1.0);
    squareTex.push_back(0.0);

    square = new Mesh(squarePts, squareTex, brickTex, texP, GL_STATIC_DRAW, GL_TRIANGLE_FAN);

    // Test textured triangle
    std::vector<GLfloat> ttPoints;
    std::vector<GLfloat> ttTex;

    ttPoints.push_back(-0.5);
    ttPoints.push_back(-0.5);
    ttPoints.push_back(0.0);
    ttPoints.push_back(0.0);
    ttPoints.push_back(0.5);
    ttPoints.push_back(0.0);
    ttPoints.push_back(0.5);
    ttPoints.push_back(-0.5);
    ttPoints.push_back(0.0);

    ttTex.push_back(0.0);
    ttTex.push_back(1.0);
    ttTex.push_back(0.5);
    ttTex.push_back(0.0);
    ttTex.push_back(1.0);
    ttTex.push_back(1.0);

    texturedTriangle = new Mesh(ttPoints, ttTex, brickTex, texP);
}

void renderFunction()
{
    //t1->draw();
    //t2->draw();
    t3->draw();

    brickTex->bind();
    //square->draw();
    texturedTriangle->draw();
    /*
    glm::mat4 model = texturedTriangle->getModelMatrix();

    printf("Model Matrix: %f, %f, %f, %f\n"
                    "              %f, %f, %f, %f\n"
                    "              %f, %f, %f, %f\n"
                    "              %f, %f, %f, %f\n",
            model[0][0], model[0][1], model[0][2], model[0][3],
            model[1][0], model[1][1], model[1][2], model[1][3],
            model[2][0], model[2][1], model[2][2], model[2][3],
            model[3][0], model[3][1], model[3][2], model[3][3]);
    */

    glm::vec3 pos = texturedTriangle->setPosition(glm::vec3(0.1, 0.1, 0.0));
    //printf("Position: (%f, %f, %f) Weight: %f\n", pos[0], pos[1], pos[2], pos[3]);
    fflush(stdout);
}

int main(int argc, char ** argv)
{
    // Start Application
    app = new Application();

    // Add Window
    Window * window = app->addWindow(320, 620, true, "Test", true);

    // Set up scene
    setupScene();

    // Set window's render function
    window->setRenderFunction(renderFunction);

    // Render Loop
    while(app->mainWindow->renderFrame());

    // Destroy application
    delete app;

    return 0;
}

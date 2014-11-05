#pragma once

#include <list>

#include "entity.h"
#include "glm.hpp"

// Class that represents camera
class Camera : public Entity
{
public:
    // Constructor
    Camera();
    // Destructor
    ~Camera();

    // Switch to this camera
    Camera * use();

    // Getter for viewMatrix
    glm::mat4 getViewMatrix();

private:
    // Camera that is currently being used
    static Camera * currentCamera;
    // List of active cameras for switching
    static std::list<Camera*> activeCameras;

    // View matrix for this camera
    glm::mat4 viewMatrix;
};
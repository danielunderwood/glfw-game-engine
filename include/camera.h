#pragma once

#include <list>

#include "entity.h"
#include "glm.hpp"

namespace GGE
{
// Class that represents camera
    class Camera : public Entity
    {
    public:
        // Constructor
        Camera(glm::vec3 direction, glm::vec3 position, glm::vec3 up);

        // Destructor
        ~Camera();

        // Switch to this camera
        Camera *use();

        // Get current camera
        static Camera *getCurrentCamera();

        // Getter for viewMatrix
        glm::mat4 getViewMatrix();

        // Override movement functions
        glm::vec3 move(glm::vec3 translation);

        glm::vec3 setPosition(glm::vec3 newPosition);

    private:
        // Camera that is currently being used
        static Camera *currentCamera;
        // List of active cameras for switching
        static std::list<Camera *> activeCameras;

        // View matrix for this camera
        glm::mat4 viewMatrix;
    };
}
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <program.h>
#include "camera.h"

namespace GGE
{
    // Declare currentCamera
    Camera *Camera::currentCamera = NULL;
    // Declare activeCameras
    std::list<Camera *> Camera::activeCameras;

    Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up) : Entity::Entity(position, direction)
    {
        // Add to list of active cameras
        activeCameras.push_back(this);

        // Set up view matrix
        viewMatrix = glm::lookAt(position, direction, up);

        // If no camera is being used, use this one
        if (!currentCamera)
            use();
    }

    Camera::~Camera()
    {
        // Remove from list of active cameras
        activeCameras.remove(this);
    }

    Camera *Camera::getCurrentCamera()
    {
        return currentCamera;
    }

    Camera *Camera::use()
    {
        // Make current camera
        currentCamera = this;

        // Return for chaining
        return this;
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return viewMatrix;
    }

    glm::vec3 Camera::move(glm::vec3 translation)
    {
        int dims = viewMatrix.length() - 1;
        // Apply translation
        for (int i = 0; i < dims; i++)
            viewMatrix[dims][i] -= translation[i];

        // TODO: Make this better
        direction += translation;

        return Entity::move(translation);
    }

    glm::vec3 Camera::setPosition(glm::vec3 newPosition)
    {
        // Set new position
        int dims = viewMatrix.length() - 1;
        for (int i = 0; i < dims; i++)
            viewMatrix[dims][i] = newPosition[i];

        return Entity::setPosition(newPosition);
    }

    glm::vec3 Camera::setDirection(glm::vec3 newDirection)
    {
        viewMatrix = glm::lookAt(position, newDirection, glm::vec3(0.0, 1.0, 0.0));

        return Entity::setDirection(newDirection);
    }
}

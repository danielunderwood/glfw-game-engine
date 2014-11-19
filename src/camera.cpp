#include <geometry.h>
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtx/rotate_vector.hpp"

#include "program.h"
#include "camera.h"

namespace GGE
{
    // Declare currentCamera
    Camera *Camera::currentCamera = NULL;
    // Declare activeCameras
    std::list<Camera *> Camera::activeCameras;

    Camera::Camera(glm::vec3 position, glm::vec3 direction) :
            Entity::Entity(position, direction)
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
        position = Entity::move(translation);

        direction -= translation;

        viewMatrix = glm::lookAt(position, direction, Y_UNIT_VECTOR);

        // Recalculate up

        return position;
    }

    glm::vec3 Camera::setPosition(glm::vec3 newPosition)
    {
        position = Entity::setPosition(newPosition);

        // TODO: Fix direction

        return position;
    }

    glm::vec3 Camera::rotate(float angle, glm::vec3 rotationAxis)
    {
        direction = Entity::rotate(angle, rotationAxis);
        up = Y_UNIT_VECTOR;

        // Recalculate up if rotation axis is not parallel to up or direction
        //if(glm::cross(rotationAxis, up) != glm::vec3(0.0, 0.0, 0.0) &&
        //        glm::cross(rotationAxis, direction) != glm::vec3(0.0, 0.0, 0.0))
        //    up = glm::cross(rotationAxis, direction);
        // Rotate with direction if rotation is about direction

        viewMatrix = glm::lookAt(position, direction, Y_UNIT_VECTOR);
        return direction;
    }

    glm::vec3 Camera::setDirection(glm::vec3 newDirection)
    {
        viewMatrix = glm::lookAt(position, newDirection, Y_UNIT_VECTOR);

        return Entity::setDirection(newDirection);
    }
}

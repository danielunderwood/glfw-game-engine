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

    Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up) :
            Entity::Entity(position, direction),
            up(up),
            right(glm::normalize(glm::cross(direction, up))),
            horizontalAngle(0),
            verticalAngle(-PI/2)
    {
        // Add to list of active cameras
        activeCameras.push_back(this);


        // Calculate direction
        direction.x = sin(verticalAngle) * sin(horizontalAngle);
        direction.y = cos(verticalAngle);
        direction.z = sin(verticalAngle) * cos(horizontalAngle);

        // Set up view matrix
        viewMatrix = glm::lookAt(position, direction, Y_UNIT_VECTOR);

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

    // TODO: Fix movement
    glm::vec3 Camera::move(glm::vec3 translation)
    {
        position = Entity::move(translation);

        viewMatrix = glm::lookAt(position, direction + position, Y_UNIT_VECTOR);

        return position;
    }

    glm::vec3 Camera::setPosition(glm::vec3 newPosition)
    {
        position = Entity::setPosition(newPosition);

        viewMatrix = glm::lookAt(position, direction, Y_UNIT_VECTOR);

        // TODO: Fix direction

        return position;
    }

    glm::vec3 Camera::rotate(float angle, glm::vec3 rotationAxis)
    {
        direction = Entity::rotate(angle, rotationAxis);

        // Rotate up and right
        up = glm::rotate(up, angle, rotationAxis - position);

        glm::vec3 rotatedRight = glm::rotate(right, angle, rotationAxis - position);
        if(glm::cross(rotatedRight, X_UNIT_VECTOR) == glm::vec3(0.0, 0.0, 0.0))
        {
            right = rotatedRight;
        }

        viewMatrix = glm::lookAt(position, direction, Y_UNIT_VECTOR);
        return direction;
    }

    glm::vec3 Camera::setDirection(glm::vec3 newDirection)
    {
        viewMatrix = glm::lookAt(position, newDirection, Y_UNIT_VECTOR);

        return Entity::setDirection(newDirection);
    }

    void Camera::updatePhysics(float deltaTime)
    {
        Entity::updatePhysics(deltaTime);
        viewMatrix = glm::lookAt(position, direction + position, Y_UNIT_VECTOR);
    }

    glm::vec3 Camera::yaw(float angle)
    {
        // Increment Angle
        horizontalAngle += angle;

        // Calculate new direction
        direction.x = sin(verticalAngle) * sin(horizontalAngle);
        direction.y = cos(verticalAngle);
        direction.z = sin(verticalAngle) * cos(horizontalAngle);

        direction = glm::normalize(direction);
        right = glm::normalize(glm::cross(direction, Y_UNIT_VECTOR));

        // Calculate view matrix
        viewMatrix = glm::lookAt(position, direction + position, Y_UNIT_VECTOR);

        return direction;
    }

    glm::vec3 Camera::pitch(float angle)
    {
        // Stop the camera from flipping over
        if(verticalAngle + angle > 0 || verticalAngle + angle < -PI)
            return direction;

        // Increment Angle
        verticalAngle += angle;

        // Calculate new direction
        direction.x = sin(verticalAngle) * sin(horizontalAngle);
        direction.y = cos(verticalAngle);
        direction.z = sin(verticalAngle) * cos(horizontalAngle);

        direction = glm::normalize(direction);

        // Calculate view matrix
        viewMatrix = glm::lookAt(position, direction + position, Y_UNIT_VECTOR);

        return direction;
    }

    glm::vec3 Camera::getUp() { return up; }
    glm::vec3 Camera::getRight() { return right; }
}

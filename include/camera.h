#pragma once

#include <list>

#include "entity.h"
#include "glm.hpp"
#include "geometry.h"

namespace GGE
{
// Class that represents camera
    class Camera : public Entity
    {
    public:
        // Constructor
        Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up = Y_UNIT_VECTOR);

        // Destructor
        ~Camera();

        // Switch to this camera
        Camera *use();

        // Get current camera
        static Camera *getCurrentCamera();

        // Getters
        glm::mat4 getViewMatrix();
        glm::vec3 getUp();
        glm::vec3 getRight();

        // Override movement functions
        glm::vec3 move(glm::vec3 translation);
        glm::vec3 setPosition(glm::vec3 newPosition);
        glm::vec3 rotate(float angle, glm::vec3 rotationAxis);
        void updatePhysics(float deltaTime);

        // Rotation Movements
        // TODO: Make these more general
        glm::vec3 yaw(float angle);     // Horizontal Rotation
        glm::vec3 pitch(float angle);   // Vertical Angle

        // Use this for changing direction until the quaternion stuff is figured out
        glm::vec3 setDirection(glm::vec3 newDirection);

    private:
        // Camera that is currently being used
        static Camera *currentCamera;
        // List of active cameras for switching
        static std::list<Camera *> activeCameras;

        // View matrix for this camera
        glm::mat4 viewMatrix;

        // Directions for camera so we don't have to calculate
        // cross products everywhere
        glm::vec3 up;
        glm::vec3 right;

        // Angles for simple camera movement
        float horizontalAngle;
        float verticalAngle;

        // Common function for recalculating direction
        void recalculateDirection();

    };
}
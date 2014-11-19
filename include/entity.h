#pragma once

#include "glm.hpp"
#include "gtc/quaternion.hpp"

namespace GGE
{
// Class to represent entity in world
// Object that has world position and can be moved, rotated, scaled
// Meshes and cameras are such objects that will inherit from here
    class Entity
    {
    public:
        // TODO: Remove these to make inheritance only class
        Entity();

        Entity(glm::vec3 position, glm::vec3 direction);

        virtual ~Entity();

        // Getters
        glm::vec3 getPosition();
        glm::vec3 getDirection();
        glm::vec3 getAcceleration();
        glm::vec3 getVelocity();
        glm::vec3 getAngularAcceleration();
        glm::vec3 getAngularVelocity();

        // Setters
        virtual glm::vec3 setPosition(glm::vec3 newPosition);
        virtual glm::vec3 setDirection(glm::vec3 newDirection);
        virtual glm::vec3 setAcceleration(glm::vec3 newAcceleration);
        virtual glm::vec3 setVelocity(glm::vec3 newVelocity);
        virtual glm::vec3 setAngularAcceleration(glm::vec3 newAngularAcceleration);
        virtual glm::vec3 setAngularVelocity(glm::vec3 newAngularVelocity);

        // Move entity's world position by vector
        virtual glm::vec3 move(glm::vec3 translation);

        // Rotate entity
        // TODO: Change to work with quaternions
        virtual glm::vec3 rotate(float angle, glm::vec3 rotationAxis);

        // Update physics based on accelerations and velocities
        virtual glm::vec3 updatePhysics(float deltaTime);

    protected:
        // TODO: Look at other structures for these, such as quaternions
        // Entity's Position in World
        glm::vec3 position;
        // Direction entity is facing
        glm::vec3 direction;
        // Acceleration of entity
        glm::vec3 acceleration;
        // Velocity of entity
        glm::vec3 velocity;
        // Angular velocity (omega) of entity
        glm::vec3 angularVelocity;
        // Angular acceleration (alpha) of entity
        glm::vec3 angularAcceleration;
    };
}
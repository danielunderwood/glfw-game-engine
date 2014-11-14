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

        // Move entity's world position by vector
        virtual glm::vec3 move(glm::vec3 translation);

        // Set entity's world position
        virtual glm::vec3 setPosition(glm::vec3 newPosition);

        // Rotate entity
        virtual glm::vec3 rotate(glm::quat rotation);

        // Set entity's direction
        virtual glm::vec3 setDirection(glm::vec3 newDirection);

    protected:
        // TODO: Look at other structures for these, such as quaternions
        // Entity's Position in World
        glm::vec3 position;
        // Direction entity is facing
        glm::vec3 direction;
    };
}
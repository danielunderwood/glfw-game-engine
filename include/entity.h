#pragma once

#include "glm.hpp"
#include "gtc/quaternion.hpp"

// Class to represent entity in world
// Object that has world position and can be moved, rotated, scaled
// Meshes and cameras are such objects that will inherit from here
class Entity
{
public:
    // TODO: Remove these to make inheritance only class
    Entity();
    ~Entity();

    // Move entity's world position by vector
    glm::vec3 move(glm::vec3 translation);

    // Set entity's world position
    glm::vec3 setPosition(glm::vec3 newPosition);

    // Rotate entity
    glm::vec3 rotate(glm::quat rotation);

    // Set entity's direction
    glm::vec3 setDirection(glm::vec3 newDirection);
protected:
    // TODO: Look at other structures for these, such as quaternions
    // Entity's Position in World
    glm::vec3 worldPosition;
    // Direction entity is facing
    glm::vec3 direction;
};
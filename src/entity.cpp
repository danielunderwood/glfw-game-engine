#include "entity.h"

#include "gtx/rotate_vector.hpp"

namespace GGE
{
    Entity::Entity() {}

    Entity::Entity(glm::vec3 position, glm::vec3 direction) : position(position), direction(direction) {}

    Entity::~Entity() {}

    glm::vec3 Entity::getPosition() { return position; }
    glm::vec3 Entity::getDirection() { return direction; }

    glm::vec3 Entity::move(glm::vec3 translation)
    {
        // Move by amount
        position += translation;

        // Return new position
        return position;
    }

    glm::vec3 Entity::setPosition(glm::vec3 newPosition)
    {
        // Set net position
        position = newPosition;

        // Return new position
        return position;
    }

    glm::vec3 Entity::rotate(float angle, glm::vec3 rotationAxis)
    {
        return direction = glm::rotate(direction, angle, rotationAxis);
    }

    glm::vec3 Entity::setDirection(glm::vec3 newDirection)
    {
        // Set direction of entity
        direction = newDirection;

        // Return new direction of entity
        return direction;
    }
}

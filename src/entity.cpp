#include "entity.h"

Entity::Entity(){}
Entity::~Entity(){}


glm::vec3 Entity::move(glm::vec3 translation)
{
    // Move by amount
    worldPosition += translation;

    // Return new position
    return  worldPosition;
}

glm::vec3 Entity::setPosition(glm::vec3 newPosition)
{
    // Set net position
    worldPosition = newPosition;

    // Return new position
    return worldPosition;
}

glm::vec3 Entity::rotate(glm::quat rotation)
{
    // TODO: Figure out how to do rotation

    // Return direction of entity
    return direction;
}

glm::vec3 Entity::setDirection(glm::vec3 newDirection)
{
    // Set direction of entity
    direction = newDirection;

    // Return new direction of entity
    return direction;
}
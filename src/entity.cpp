#include "entity.h"

#include "gtx/rotate_vector.hpp"

namespace GGE
{
    Entity::Entity() :
        acceleration(glm::vec3(0.0, 0.0, 0.0)),
        velocity(glm::vec3(0.0, 0.0, 0.0)),
        angularAcceleration(glm::vec3(0.0, 0.0, 0.0)),
        angularVelocity(glm::vec3(0.0, 0.0, 0.0))
    {}

    Entity::Entity(glm::vec3 position, glm::vec3 direction) :
            position(position), direction(direction) {}

    Entity::~Entity() {}

    glm::vec3 Entity::getPosition() { return position; }
    glm::vec3 Entity::getDirection() { return direction; }
    glm::vec3 Entity::getAcceleration() { return acceleration; }
    glm::vec3 Entity::getVelocity() { return velocity; }
    glm::vec3 Entity::getAngularAcceleration() { return angularAcceleration; }
    glm::vec3 Entity::getAngularVelocity() { return angularVelocity; }

    glm::vec3 Entity::move(glm::vec3 translation)
    {
        // Move by amount
        position += translation;

        // Return new position
        return position;
    }

    glm::vec3 Entity::rotate(float angle, glm::vec3 rotationAxis)
    {
        return direction = glm::rotate(direction, angle, rotationAxis);
    }

    void Entity::updatePhysics(float deltaTime)
    {
        velocity += deltaTime * acceleration;
        position += velocity;

        // TODO: Angular stuff
    }

    glm::vec3 Entity::setPosition(glm::vec3 newPosition)
    { return position = newPosition; }
    glm::vec3 Entity::setDirection(glm::vec3 newDirection)
    { return direction = newDirection; }
    glm::vec3 Entity::setAcceleration(glm::vec3 newAcceleration)
    { return acceleration = newAcceleration; }
    glm::vec3 Entity::setVelocity(glm::vec3 newVelocity)
    { return velocity = newVelocity; }
    glm::vec3 Entity::setAngularAcceleration(glm::vec3 newAngularAcceleration)
    { return angularAcceleration = newAngularAcceleration; }
    glm::vec3 Entity::setAngularVelocity(glm::vec3 newAngularVelocity)
    { return angularVelocity = newAngularVelocity; }
}

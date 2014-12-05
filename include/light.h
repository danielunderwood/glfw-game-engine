#pragma once

#include "glm.hpp"

#include "entity.h"
#include "color.h"

namespace GGE
{
    // Light types
    // These lights are similar, but differ in math behind them
    enum LightType
    {
        LIGHT_POINT,    // Light irradiates from position
        LIGHT_AMBIENT,  // Lights everywhere within area
        LIGHT_SPOT      // Light irradiates in direction of light (has spot size)
    };

    // Class to represent light in world
    class Light : public Entity
    {
    public:
        // Default constructor
        Light();
        // Constructor
        Light(glm::vec3 position, glm::vec3 direction, LightType type, Color4 color);
        // Destructor
        virtual ~Light();

        // Getters
        Color4 getColor();
        LightType getLightType();

    protected:
        // Color of light
        Color4 color;
        // Type of light
        LightType type;
    };

    // Class to represent point light
    class PointLight : public Light
    {
    public:
        // Constructor
        PointLight(glm::vec3 position, glm::vec3 direction, Color4 color);
        // Destryctor
        ~PointLight();
    };

    // Class to represent ambient light
    class AmbientLight : public Light
    {
    public:
        // Constructor
        AmbientLight(glm::vec3 position, glm::vec3 direction, Color4 color);
        // Destructor
        ~AmbientLight();
    };

    // Class to represent spotlight
    class SpotLight : public Light
    {
    public:
        // Constructor
        SpotLight(glm::vec3 position, glm::vec3 direction, Color4 color);
        // Destructor
        ~SpotLight();
    };
}
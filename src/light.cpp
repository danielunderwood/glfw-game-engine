#include "light.h"

namespace GGE
{
    Light::Light(){}

    Light::Light(glm::vec3 position, glm::vec3 direction, LightType type, Color4 color) :
        Entity(position, direction),
        type(type),
        color(color)
    {
    }

    Light::~Light() { }

    PointLight::PointLight(glm::vec3 position, glm::vec3 direction, Color4 color) :
        Light(position, direction, LIGHT_POINT, color)
    {
    }

    AmbientLight::AmbientLight(glm::vec3 position, glm::vec3 direction, Color4 color) :
        Light(position, direction, LIGHT_AMBIENT, color)
    {
    }

    SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, Color4 color) :
        Light(position, direction, LIGHT_SPOT, color)
    {
    }

    Color4 Light::getColor() { return color; }
    LightType Light::getLightType() { return type; }
}
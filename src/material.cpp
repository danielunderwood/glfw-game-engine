#include "material.h"

namespace GGE
{
    Material::Material(TextureSet * textures, LightingProperties * lightingProperties) :
        textures(textures),
        lightingProperties(lightingProperties)
    {
    }

    Material::~Material(){}
}
#pragma once

#include <vector>

#include "glew.h"
#include "glfw3.h"

#include "texture.h"
#include "color.h"

namespace GGE
{
    // Enum of color properties to allow for other ways of easy looping
    enum LightingColors
    {
        AMBIENT_COLOR,
        DIFFUSE_COLOR,
        SPECULAR_COLOR,
        TRANSMISSION_COLOR,
        EMITTANCE_COLOR,
    };

    // Enum for light travel (ior, shininess, dissolve)
    enum LightTravelProperties
    {
        SHININESS,
        INDEX_OF_REFRACTION,
        DISSOLVE
    };

    // Struct for lighting properties of material
    typedef struct LightingProperties
    {
        // Color properties
        // TODO: Use union
        Color3 ambientColor, diffuseColor, specularColor, transmissionColor, emissionColor;

        // Light travel properties
        // TODO: Use union
        float shininess, indexOfRefraction, dissolve;

        // Illumination model for material
        int illuminationModel;

        LightingProperties() : ambientColor(Color3()),
                               diffuseColor(Color3()),
                               specularColor(Color3()),
                               transmissionColor(Color3()),
                               emissionColor(Color3())
        {}
    } LightingProperties;

    // Struct to represent texture maps
    typedef struct TextureSet
    {
        Texture * ambientTexture, * diffuseTexture, * specularTexture, * normalTexture;

        // Constructor
        // TODO: See if these constructors are really needed
        TextureSet() {}
    } TextureSet;

    // Class describing the material for a mesh
    class Material
    {
    public:
        // Constructor
        Material(TextureSet * textures, LightingProperties * lightingProperties);
        // Destructor
        ~Material();

    private:
        // Textures for material
        TextureSet * textures;

        // Lighting properties
        LightingProperties * lightingProperties;

        // TODO: Mapping compatability
    };
}
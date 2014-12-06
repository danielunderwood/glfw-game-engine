#version 150 core

// Light
struct Light
{
    vec3 position;
    vec3 direction;
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
};

// Material
struct Material
{
    // Texture Flags
    bool hasAmbientTexture;
    bool hasDiffuseTexture;
    bool hasSpecularTexture;

    // Textures
    sampler2D ambientTexture;
    sampler2D diffuseTexture;
    sampler2D specularTexture;

    // Colors
    // TODO: Implement emission and transmission
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;

    // Properties
    // TODO: Implement index of refraction and dissolve
    float shininess;
};

uniform vec3 cameraPosition;    // Position of current camera

uniform Light light;            // Light in scene
                                // TODO: Make work for multiple lights
uniform Material material;      // Material for what is being rendered

// -- Inputs --
in vec2 lerpTextureCoordinates;
in vec3 lerpNormals;
in vec3 lerpPosition;

// -- Outputs --

void main()
{
    // Calculate Colors
    vec3 ambientColor = calculateAmbientColor();
    vec3 diffuseColor = calculateDiffuseColor();
    vec3 specularColor = calculateSpecularColor();

    // Final Color
    // TODO: Make work with transparency
    out vec4 finalColor = ambientColor + diffuseColor + specularColor;
}

vec3 calculateAmbientColor()
{
        // Ambient Color
        vec3 ambientColor;
        if(material.hasAmbientTexture)
        {
            ambientColor = tex(material.ambientTexture, lerpTextureCoorinates).xyz;
        }
        else
        {
            ambientColor = material.ambientColor;
        }

        ambientColor.xyz *= light.ambientColor.xyz;
        return ambientColor;
}

vec3 calculateDiffuseColor()
{
    // Calculate from surface to light
    vec3 l = lerpPosition - light.position;

    // Diffuse Color
    vec3 diffuseColor;
    if(material.hasDiffuseTexture)
    {
        diffuseColor = tex(material.diffuseTexture, lerpTextureCoordinates).xyz;
    }
    else
    {
        diffuseColor = material.diffuseColor;
    }

    diffuseColor.xyz *= max(0, dot(normalize(l), normalize(lerpNormals))) * light.diffuseColor.xyz;
    return diffuseColor;
}

vec3 calculateSpecularColor()
{
    // Reflected Ray Term
    vec3 r = 2 * dot(normalize(light.position), normalize(lerpNormals)) * normalize(lerpNormals);
    r -= light.position;

    // Specular Multiplication Term
    float specularMult = pow(max(0, dot(normalize(r), normalize(lerpPosition - cameraPosition))), shininess);

    // Specular Color
    vec3 specularColor;
    if(material.hasSpecularTexture)
    {
        specularColor = tex(material.specularTexture, lerpTextureCoordinates).xyz;
    }
    else
    {
        specularColor = material.specularColor;
    }

    specularColor.xyz *= specularMult * light.specularColor.xyz;
    return specularColor;
}
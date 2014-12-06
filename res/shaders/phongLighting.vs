#version 150 core

// -- Inputs --
in vec3 modelPosition;          // Position of what is being rendered
in vec3 modelNormal;            // Normal of vertex being rendered
in vec2 textureCoordinates;     // UV Coordinates for what is being rendered

// Transform Matrices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// -- Outputs --
out vec2 lerpTextureCoordinates;
out vec3 lerpNormals;
out vec3 lerpPosition;

void main()
{
    // Calculate Vertex Position
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(modelPosition, 1.0);

    // Interpolate Values for Fragment Shader
    lerpTextureCoordinates = textureCoordinates;
    lerpNormals = modelNormal;
    lerpPosition = modelPosition;
}
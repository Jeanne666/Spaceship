#version 400

uniform sampler2D texSampler;

// Surfel: a SURFace ELement. All coordinates are in world space
in vec2 surfel_texCoord;
in vec3 surfel_position;
in vec4 surfel_color;
in vec3 surfel_normal;

// Camera position in world space
in vec3 cameraPosition;

// Resulting color of the fragment shader
out vec4 outColor;

void main()
{
    outColor = texture(texSampler, surfel_texCoord);
}

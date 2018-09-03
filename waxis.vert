#version 330

layout (location = 0) in vec3 vertex;
layout (location = 6) in vec4 colour;

out vec4 fragColour;

uniform mat4 viewProjectionMatrix;

void main(void)
{
    fragColour = colour;

    gl_Position = viewProjectionMatrix * vec4(vertex, 1.0);
}

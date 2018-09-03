#version 330

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 center;
layout (location = 2) in mat4 modelMatrix;

out vec4 fragColour;

uniform mat4 viewProjectionMatrix;

void main(void)
{
    fragColour = vec4(1.0, 1.0, 1.0, 1.0);

    gl_Position = viewProjectionMatrix * (modelMatrix * vec4(vertex, 1.0) + vec4(center, 0.0));
}

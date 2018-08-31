#version 330

layout (location = 0) in vec3 qt_Vertex;
layout (location = 1) in vec3 instCenter;
layout (location = 2) in mat4 instModelMatrix;

uniform mat4 qt_ViewProjectionMatrix;

void main(void)
{
    gl_Position = qt_ViewProjectionMatrix * (instModelMatrix * vec4(qt_Vertex, 1.0) + vec4(instCenter, 0.0));
}

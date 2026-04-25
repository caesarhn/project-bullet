#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 texCoord;


void main() {
    texCoord = inTexCoord;
    gl_Position = vec4((inPos.x / 8), (inPos.y / 4.5), inPos.z, 1.0);

}
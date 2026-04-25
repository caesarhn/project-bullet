#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 projection;
} ubo;

layout(set = 1, binding = 0) uniform UniformBufferEntity {
    mat4 model;
    ivec4 controlAnimation;
    ivec4 animationDetail;
    ivec4 samplerIndex;
    ivec4 object;
} entities;

layout(location = 0) in vec3 inPos;


void main() {
    gl_Position = vec4(inPos, 1.0);
    gl_Position = ubo.projection * ubo.view * entities.model * vec4(inPos, 1.0);

}
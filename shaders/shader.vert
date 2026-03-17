#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 projection;
} ubo;

layout(set = 1, binding = 0) uniform UniformBufferCharacter {
    mat4 model;
    ivec4 controlAnimation;
    ivec4 animationDetail;
    ivec4 samplerIndex;
    ivec4 object;
} character;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) flat out ivec4 control_animation;
layout(location = 3) flat out ivec4 detail_animation;
layout(location = 4) flat out ivec4 samplerIdx;
layout(location = 5) flat out ivec4 objectType;

void main() {
    gl_Position = ubo.projection * ubo.view * character.model * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
    control_animation = character.controlAnimation;
    detail_animation = character.animationDetail;
    samplerIdx = character.samplerIndex;
    objectType = character.object;
}
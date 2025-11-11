#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 set_binding;
    vec4 player_state;
    vec4 animationIdx;
} ubo;

layout(set = 2, binding = 0) uniform UniformBufferChar {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 set_bindings;
    vec4 player_state;
    vec4 animationIdx;
} character;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec2 texture_location;
layout(location = 3) out vec2 p_state;

void main() {
    gl_Position = character.proj * character.view * character.model * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
    texture_location = character.set_bindings.xy;
    p_state = character.player_state.xy;
}
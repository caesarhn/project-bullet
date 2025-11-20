#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 projection;
} ubo;

layout(set = 2, binding = 0) uniform UniformBufferCharacter {
    mat4 model;
    vec4 controlAnimation;
    vec4 animationDetail;
} character;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec4 control_animation;
layout(location = 3) out vec4 detail_animation;

void main() {
    vec4 pos = ubo.projection * ubo.view * character.model * vec4(inPosition, 1.0);
    gl_Position = vec4(pos.x * -1.0, pos.yzw);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
    control_animation = character.controlAnimation;
    detail_animation = character.animationDetail;

    const vec2 positions[3] = vec2[3](
        vec2(0.0, -0.5),   // Bottom vertex
        vec2(0.5, 0.5),    // Right vertex  
        vec2(-0.5, 0.5)    // Left vertex
    );

    const vec3 colors[3] = vec3[3](
        vec3(1.0, 0.5, 0.0),   // Bottom vertex
        vec3(1.0, 0.5, 0.0),    // Right vertex  
        vec3(1.0, 0.5, 0.0)    // Left vertex
    );

    vec2 position = positions[gl_VertexIndex];
    fragColor = colors[gl_VertexIndex];
    gl_Position = vec4(position, 0.0, 1.0);
}
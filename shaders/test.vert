#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 texCoord;

layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    fragColor = inColor;

    //     const vec2 positions[3] = vec2[3](
    //     vec2(0.0, -0.5),   // Bottom vertex
    //     vec2(0.5, 0.5),    // Right vertex  
    //     vec2(-0.5, 0.5)    // Left vertex
    // );

    // const vec3 colors[3] = vec3[3](
    //     vec3(1.0, 0.5, 0.0),   // Bottom vertex
    //     vec3(1.0, 0.5, 0.0),    // Right vertex  
    //     vec3(1.0, 0.5, 0.0)    // Left vertex
    // );

    // vec2 position = positions[gl_VertexIndex];
    // fragColor = colors[gl_VertexIndex];
    // gl_Position = vec4(position, 0.6, 1.0);
}

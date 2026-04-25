#version 450

layout(set = 0, binding = 0) uniform sampler2D Samplers[1];
layout(set = 0, binding = 1) uniform sampler2D Effect[8];

layout(push_constant) uniform Constant {
    int animationIdx;
} pc;

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec2 texCoord;

void main() {

    // outColor = vec4(1.0, 0.0, 0.0, 1.0); // merah
    outColor = texture(Samplers[0], texCoord);
}
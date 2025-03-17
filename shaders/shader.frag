#version 450

layout(set = 0, binding = 1) uniform sampler2D texSampler;
layout(set = 1, binding = 0) uniform sampler2D texSampler1;
layout(set = 1, binding = 1) uniform sampler2D texSampler2;
layout(set = 1, binding = 2) uniform sampler2D texSampler3;
layout(set = 1, binding = 3) uniform sampler2D texSampler4;
layout(set = 1, binding = 4) uniform sampler2D texSampler5;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec2 texture_location;

layout(location = 0) out vec4 outColor;

void main() {
    vec4 texColor;
    const float EPSILON = 0.01;

    if(abs(texture_location.x - 0.0) < EPSILON && abs(texture_location.y - 1.0) < EPSILON){
        texColor = texture(texSampler, fragTexCoord);
    }
    else if(abs(texture_location.x - 1.0) < EPSILON && abs(texture_location.y - 0.0) < EPSILON){
        texColor = texture(texSampler1, fragTexCoord);
    }
    else if(abs(texture_location.x - 1.0) < EPSILON && abs(texture_location.y - 1.0) < EPSILON){
        texColor = texture(texSampler2, fragTexCoord);
    }
    else if(abs(texture_location.x - 1.0) < EPSILON && abs(texture_location.y - 2.0) < EPSILON){
        texColor = texture(texSampler3, fragTexCoord);
    }
    else if(abs(texture_location.x - 1.0) < EPSILON && abs(texture_location.y - 3.0) < EPSILON){
        texColor = texture(texSampler4, fragTexCoord);
    }
    else if(abs(texture_location.x - 1.0) < EPSILON && abs(texture_location.y - 4.0) < EPSILON){
        texColor = texture(texSampler5, fragTexCoord);
    }else{
        texColor = vec4(fragColor, 1.0);
    }

    if (texColor.a < 0.1) discard;
    outColor = texColor;
}
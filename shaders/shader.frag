#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 set_bindings;
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

layout(set = 0, binding = 1) uniform sampler2D texSampler;
layout(set = 1, binding = 0) uniform sampler2D texSampler1;
layout(set = 1, binding = 1) uniform sampler2D texSampler2;
layout(set = 1, binding = 2) uniform sampler2D texSampler3;
layout(set = 1, binding = 3) uniform sampler2D texSampler4;
layout(set = 1, binding = 4) uniform sampler2D texSampler5;
layout(set = 1, binding = 5) uniform sampler2D texSampler6;
layout(set = 1, binding = 6) uniform sampler2D texSampler7;

layout(set = 3, binding = 0) uniform sampler2D characterIdleSampler;
layout(set = 3, binding = 1) uniform sampler2D characterWalkSampler;
layout(set = 3, binding = 2) uniform sampler2D characterRunSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec2 texture_location;
layout(location = 3) in vec2 p_state;

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
    }
    else if(abs(texture_location.x - 1.0) < EPSILON && abs(texture_location.y - 5.0) < EPSILON){
        float x = 0.125 * fragTexCoord.x;
        float y = 0.25 * fragTexCoord.y;
        if(fragTexCoord.x == 0.0){
            x = x - 0.125;
        }
        vec2 newTexCoord = vec2(x, y);
        texColor = texture(texSampler6, newTexCoord);
    }else{
        texColor = vec4(fragColor, 1.0);
    }

    float cc = abs(p_state.x - 1.0);
    if(abs(p_state.x - 1.0) < EPSILON){
        float idleIdx = p_state.y;
        vec2 newTexCoord;
        if(abs(idleIdx - 0.0) < EPSILON){
            newTexCoord = vec2(0.125*fragTexCoord.x, 0.25*fragTexCoord.y);
        }
        else if(abs(idleIdx - 1.0) < EPSILON){
            newTexCoord = vec2(0.25*fragTexCoord.x+(0.125-(0.125*fragTexCoord.x)), 0.25*fragTexCoord.y);
        }
        else if(abs(idleIdx - 2.0) < EPSILON){
            newTexCoord = vec2(0.375*fragTexCoord.x+(0.25-(0.25*fragTexCoord.x)), 0.25*fragTexCoord.y);
        }
        else if(abs(idleIdx - 3.0) < EPSILON){
            newTexCoord = vec2(0.5*fragTexCoord.x+(0.375-(0.375*fragTexCoord.x)), 0.25*fragTexCoord.y);
        }
        else if(abs(idleIdx - 4.0) < EPSILON){
            newTexCoord = vec2(0.625*fragTexCoord.x+(0.5-(0.5*fragTexCoord.x)), 0.25*fragTexCoord.y);
        }
        else if(abs(idleIdx - 5.0) < EPSILON){
            newTexCoord = vec2(0.75*fragTexCoord.x+(0.625-(0.625*fragTexCoord.x)), 0.25*fragTexCoord.y);
        }
        else if(abs(idleIdx - 6.0) < EPSILON){
            newTexCoord = vec2(0.875*fragTexCoord.x+(0.75-(0.75*fragTexCoord.x)), 0.25*fragTexCoord.y);
        }
        else if(abs(idleIdx - 7.0) < EPSILON){
            newTexCoord = vec2(1.0*fragTexCoord.x+(0.875-(0.875*fragTexCoord.x)), 0.25*fragTexCoord.y);
        }
        texColor = texture(texSampler6, newTexCoord);
    }
    else if(abs(p_state.x - 2.0) < EPSILON){
        float animateIdx = p_state.y;
        vec2 newTexCoord;
        if(abs(animateIdx - 0.0) < EPSILON){
            newTexCoord = vec2(0.125*fragTexCoord.x, 0.25*fragTexCoord.y);
        }
    }

    // if(ubo.playerState > 0){
    //     texColor = vec4(1.0, 1.0, 1.0, 1.0);
    // }

    if (texColor.a < 0.1) discard;
    outColor = texColor;
}
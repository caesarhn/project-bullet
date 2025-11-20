#version 450

layout(set = 0, binding = 1) uniform sampler2D texSampler;
// layout(set = 1, binding = 0) uniform sampler2D texSampler1;
// layout(set = 1, binding = 1) uniform sampler2D texSampler2;
// layout(set = 1, binding = 2) uniform sampler2D texSampler3;
// layout(set = 1, binding = 3) uniform sampler2D texSampler4;
// layout(set = 1, binding = 4) uniform sampler2D texSampler5;
// layout(set = 1, binding = 5) uniform sampler2D texSampler6;
// layout(set = 1, binding = 6) uniform sampler2D texSampler7;

layout(set = 3, binding = 0) uniform sampler2D characterIdleSampler;
layout(set = 3, binding = 1) uniform sampler2D characterWalkSampler;
layout(set = 3, binding = 2) uniform sampler2D characterRunSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec4 control_animation;
layout(location = 3) in vec4 detail_animation;

layout(location = 0) out vec4 outColor;

const float EPSILON = 0.01;

void renderAnimation(vec4 control, vec4 detail, out vec4 result){
    float sub_animation_range = 1.0 / detail.x;
    float frame_range = 1.0 / detail.y;
    float anim_range = 1.0 / detail.x;

    float tex_loc_anim_x = frame_range * control.w + (frame_range * fragTexCoord.x);
    float tex_loc_anim_y = anim_range * control.y + (anim_range * fragTexCoord.y);

    vec2 newTexCoord = vec2(tex_loc_anim_x, tex_loc_anim_y);
    
    if(abs(control.x - 0.0) < EPSILON){
        result = texture(characterIdleSampler, newTexCoord);
    }
    else if(abs(control.x - 1.0) < EPSILON){
        result = texture(characterWalkSampler, newTexCoord);
    }
    else if(abs(control.x - 2.0) < EPSILON){
        result = texture(characterRunSampler, newTexCoord);
    }else{
        result = vec4(1.0, 0.0, 0.0, 1.0);
    }
}

void main() {
    vec4 texColor;

    renderAnimation(control_animation, detail_animation, texColor);
    // texColor = vec4(fragColor, 1.0);

    if (texColor.a < 0.1) discard;
    outColor = texColor;
}
#version 450

layout(set = 2, binding = 0) uniform sampler2D characterSampler[4];

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) flat in ivec4 control_animation;
layout(location = 3) flat in ivec4 detail_animation;
layout(location = 4) flat in ivec4 samplerIdx;
layout(location = 5) flat in ivec4 objectType;

layout(location = 0) out vec4 outColor;

const float EPSILON = 0.01;

void renderAnimation(ivec4 control, ivec4 detail, out vec4 result){
    float sub_animation_range = 1.0 / float(detail.x);
    float frame_range = 1.0 / float(detail.y);
    float anim_range = 1.0 / float(detail.x);

    float tex_loc_anim_x = frame_range * float(control.w) + (frame_range * fragTexCoord.x);
    float tex_loc_anim_y = anim_range * float(control.y) + (anim_range * fragTexCoord.y);

    vec2 newTexCoord = vec2(tex_loc_anim_x, tex_loc_anim_y);
    
    if(control.x == 0){
        result = texture(characterSampler[samplerIdx.x], newTexCoord);
    }
    else if(control.x == 1){
        result = texture(characterSampler[samplerIdx.y], newTexCoord);
    }
    else if(control.x == 2.0){
        result = texture(characterSampler[samplerIdx.z], newTexCoord);
    }
    else if(control.x < 0){
        result = vec4(1.0, 1.0, 0.0, 1.0);
    }
    else{
        result = vec4(1.0, 0.0, 0.0, 1.0);
    }
}

void main() {
    vec4 texColor;

    if(objectType.x == 1){
        renderAnimation(control_animation, detail_animation, texColor);
    }
    else if(objectType.x == 0){
        texColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if(objectType.x == 2){
        texColor = vec4(fragColor, 1.0);
    }
    // texColor = vec4(fragColor, 1.0);

    if (texColor.a < 0.1) discard;
    outColor = texColor;
}
#version 450

layout(set = 2, binding = 0) uniform sampler2D Samplers[11];
layout(set = 3, binding = 0) buffer TileBuffer {
    int tiles[];
};

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
        result = texture(Samplers[samplerIdx.x], newTexCoord);
    }
    else if(control.x == 1){
        result = texture(Samplers[samplerIdx.y], newTexCoord);
    }
    else if(control.x == 2.0){
        result = texture(Samplers[samplerIdx.z], newTexCoord);
    }
    else if(control.x < 0){
        result = vec4(1.0, 1.0, 0.0, 1.0);
    }
    else{
        result = vec4(1.0, 0.0, 0.0, 1.0);
    }
}

float custom_precision(float value){
    int buff = int(floor(value * 100));

    return float(buff / 100.0);
}

// void renderTileMap(int width, out vec4 result){
//     int index_x = int(floor(float(width) * fragTexCoord.x));
//     int index_y = int(floor(float(width) * fragTexCoord.y));
//     float atlas_x = fract(fragTexCoord.x * float(width));
//     float atlas_y = fract(fragTexCoord.y * float(width));
//     vec2 atlas_coord = vec2(atlas_x, atlas_y);
//     int index = (index_y * width) + index_x;
//     if(atlas_x > 0.01 && atlas_x < 0.99){
//         result = texture(Samplers[tiles[index]], atlas_coord);
//     }
// }

void renderTileMap(int width, out vec4 result){

    // === hitung posisi tile ===
    float fx = fragTexCoord.x * float(width);
    float fy = fragTexCoord.y * float(width);

    int index_x = int(floor(fx));
    int index_y = int(floor(fy));

    // clamp biar tidak keluar array
    index_x = clamp(index_x, 0, width - 1);
    index_y = clamp(index_y, 0, width - 1);

    int index = index_y * width + index_x;

    // === ambil UV lokal tile ===
    vec2 localUV = vec2(fract(fx), fract(fy));

    // === optional: half pixel offset (anti bleeding ringan) ===
    float texSize = float(textureSize(Samplers[0], 0).x);
    float texel = 1.0 / texSize;

    localUV = localUV * (1.0 - texel) + texel * 0.5;

    // === ambil texture index ===
    int texId = tiles[index];

    // safety (hindari crash)
    texId = clamp(texId, 0, 10 - 1);

    result = texture(Samplers[10], vec2(localUV.x * 0.3, localUV.y * 0.3));
    if(index_x == 2){
        result = texture(Samplers[10], vec2((localUV.x * 0.3) + 0.3, (localUV.y * 0.3) + 0.3));
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
    else if(objectType.x == 3){
        renderTileMap(10, texColor);
    }
    // texColor = vec4(fragColor, 1.0);

    if (texColor.a < 0.1) discard;
    outColor = texColor;
}
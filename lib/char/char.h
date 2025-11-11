// #pragma once
// #include <glm/glm.hpp>
// #include <string>
// #include <vector>

// struct textureCoord
// {
//     /* data */
//     std::string state;
//     std::vector<glm::vec4> coord;

//     textureCoord(std::string state_e = "", std::vector<glm::vec4> coord_e) : state(state_e), coord(coord_e) {}
// };

// class Character {
// private:
//     std::string id;
//     int atk;
//     int hp;
//     glm::vec2 loc;
//     float speed;
//     int textureIdx;
//     int charState;
//     // std::vector<textureCoord> textureCoord_8s_64 = {
//     //     textureCoord("idle", std::vector<glm::vec4>{
//     //         glm::vec4(0.0f, 0.0f, 0.125f, 0.25f),
//     //         glm::vec4(0.125f, 0.0f, 0.25f, 0.25f),
//     //         glm::vec4(0.25f, 0.0f, 0.375f, 0.25f),
//     //         glm::vec4(0.375f, 0.0f, 0.5f, 0.25f),
//     //         glm::vec4(0.5f, 0.0f, 0.625f, 0.25f),
//     //         glm::vec4(0.625f, 0.0f, 0.750f, 0.25f),
//     //         glm::vec4(0.750f, 0.0f, 0.875f, 0.25f),
//     //         glm::vec4(0.875f, 0.0f, 1.0f, 0.25f)
//     //     }),
//     // }
    

// public:
//     Character (std::string id);
//     void setAttribute(int atk, int hp, glm::vec2 loc, float spd, int tex_idx);
//     void changeTexture(int tex_idx);
//     int damaged(int damage);
//     int regeneration(int regen);
//     float* getLocation();
//     void moveX(float direction);
// };
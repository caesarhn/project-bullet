#pragma once
#include <string.h>
#include <vector>
#include <glm/glm.hpp>
//All Skill

struct Skill{
    std::string id;
    std::string name;
    int physicalDamage;
    int magicDamage;
};

class SkillEntity{
    std::vector<Skill> skills;

    const std::string SKILL_PUNCH = "punch";

    SkillEntity(){

        skills.push_back({SKILL_PUNCH, "punch", 10, 0});
    }
};

struct Walk
{
    int walkAnimation = 0;
    int walkFrame = 0;
    int max;

    Walk(int max) : max(max){}

    void walked(float *character){
        if(walkFrame == 60 / max){
            *character = (float)(walkAnimation);
            if(walkAnimation == max){
                walkAnimation = 0;
            }else{
                walkAnimation++;
            }
            walkFrame = 0;
        }else{
            walkFrame++;
        }
    }
};


struct Animation
{
    int animation = 0;
    int frame = 0;
    int max;
    glm::vec2 goTo;

    Animation(int max) : max(max){}

    void animate(float *character){
        if(frame == 60 / max){
            *character = (float)(animation);
            if(animation == max){
                animation = 0;
            }else{
                animation++;
            }
            frame = 0;
        }else{
            frame++;
        }
    }

    void setGoto(glm::vec2 go){
        goTo = go;
    }
};
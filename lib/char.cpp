#include <lib/char.h>

Character::Character (char *id, int atk, int hp, float locx, float locy, float speed){
    id = id;
    atk = atk;
    hp = hp;
    loc[0] = locx;
    loc[1] = locy;
    speed = speed;
}

int Character::damaged(int damage){
    hp = hp - damage;

    return hp;
}

int Character::regeneration(int regen){
    hp = hp + regen;

    return hp;
}

float *Character::getLocation (){
    return loc;
}

void Character::moveX(float direction){
    loc[0] = loc[0] + (speed * direction);
}
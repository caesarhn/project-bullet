#pragma once
#include <vector>

#include <app/gameConstant.h>

struct Enemies{
    int id;
    char name[30];
    int hp;
    std::vector<int> damage;
    std::vector<int> specialDamage;
};

struct Attacks{
    char name[30];
    int hits;
    int weapon;
    float criticalChange;
};

struct  Weapons{
    int id;
    char name[30];
    int elemental;
    int damage;
    int weightType;
    int quality;
};

class Mechanics{
private:
    /* data */
public:
    Mechanics();
    ~Mechanics();

    std::vector<Attacks> attacks;
    std::vector<Weapons> weapons;
    std::vector<Enemies> enemies;

    void initEnemies();
    void initWeapons();
    void initAttacks();

};


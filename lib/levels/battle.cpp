#pragma once
#include <level.h>

void BattleLevel::initBattle(std::vector<int> heroes, std::vector<int> villains){
    heroId.resize(heroes.size());
    villainId.resize(villains.size());

    heroId = heroes;
    villainId = villains;
}

void BattleLevel::clearBattle(){
    heroId = static std::vector<int>();
    villainId = static std::vector<int>();
}
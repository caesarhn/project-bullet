#pragma once
#include <strings.h>
#include <vector>
#include <char/mob.h>

class Level
{
private:
    std::string levelType;
public:
};

class WorldLevel : public Level{
private:
    std::vector<std::string> worldList;
    const int MAIN_WORLD = 0;
public:
    bool enableMove;

    void initWorld();
    void mainWorld();
};

class BattleLevel : public Level{
public:
    static std::vector<int> heroId;
    static std::vector<int> villainId;
    static bool isHeroTurn;

    void initBattle(std::vector<int> heroes, std::vector<int> vilains);
    void clearBattle();
};


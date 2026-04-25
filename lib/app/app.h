#pragma once
#include <vulkan/init.h>
#include <app/mechanics/mechanics.h>
// #include <levels/level.h>

struct BattleEnemy{
    Enemies enemyStat;
    int hp;
};


class Application
{
private:
    VulkanApplication* Vulkan;
    int event;
    
    //Battle
    BattleEnemy currentEnemy;

public:
    Application();
    void mainLoop();
    void battle(Enemies setEnemy);
};

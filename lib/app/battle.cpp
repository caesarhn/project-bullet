#include <app/app.h>

void Application::battle(Enemies setEnemy){
    currentEnemy.enemyStat = setEnemy;
    currentEnemy.hp = setEnemy.hp;
}
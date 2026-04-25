#include "mechanics.h"

void Mechanics::initWeapons(){
    weapons = {
        {
            {0},
            {"hand"},
            {ELEMENTAL_PHYSICAL},
            {10},
            {WEIGHT_TYPE_LIGHT},
            {10}
        },{
            {1},
            {"fighter hand"},
            {ELEMENTAL_PHYSICAL},
            {15},
            {WEIGHT_TYPE_LIGHT},
            {10}
        }
    };
}
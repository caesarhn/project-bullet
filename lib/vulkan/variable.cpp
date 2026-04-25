#include <vulkan/init.h>

std::chrono::time_point<std::chrono::high_resolution_clock> VulkanApplication::lastFrameTime;

void VulkanApplication::initVariables(){
    lastFrameTime = std::chrono::high_resolution_clock::now();
    
    textureAssets = {
        "src/char/char1_idle1.png",
        "src/char/char1_idle2.png",
        "src/char/char1_idle3.png",
        "src/char/char1_idle4.png",
        "src/char/char1_idle5.png",
        "src/char1/idle.png"
    };

    characterAssets = {
        "src/char1/idle.png",
        "src/char1/walk.png",
        "src/char1/run.png",
        "src/char2/idle.png",
        "src/explosion/explode_c.png",
        "src/map/tiles/test_1.png",
        "src/map/tiles/test_2.png",
        "src/map/tiles/test_3.png",
        "src/map/tiles/test_4.png",
        "src/map/tiles/test_5.png",
        "src/map/tiles/tiless.jpg",
        "src/char_enemies/minotaur.png",
    };

    battleEnemyAssets = {
        "src/char_enemies/minotaur.png",
    };

    battleEffectAssets = {
        "src/explosion/explode_a.png",
        "src/explosion/explode_b.png",
        "src/explosion/explode_c.png",
        "src/explosion/explode_d.png",
        "src/explosion/explode_e.png",
        "src/explosion/explode_f.png",
        "src/explosion/explode_g.png",
        // "src/explosion/explode-b.png",
    };

    vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
    };

    vertices2 = {
        {{-0.5f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

        {{-5.0f, -5.0f, -1.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{5.0f, -5.0f, -1.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{5.0f, 5.0f, -1.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-5.0f, 5.0f, -1.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

        //Battle vertex
        {{5.0f, -3.0f, 0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{2.0f, -3.0f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{2.0f, 1.0f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{5.0f, 1.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    };

    tileBlock = {
        {{-1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
    };

    tileLines = {
        {{-10.0f, 0.014f, 0.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
        {{10.0f, 0.014f, 0.0f}, {0.8f, 0.8f, 0.5f}, {0.0f, 0.0f}},
        {{-10.0f, -0.014f, 0.0f}, {0.8f, 0.8f, 0.5f}, {1.0f, 1.0f}},
        {{10.0f, -0.014f, 0.0f}, {0.8f, 0.8f, 0.5f}, {0.0f, 1.0f}},

        {{0.001f, 10.0f, 0.0f}, {0.8f, 0.8f, 0.8f}, {1.0f, 0.0f}},
        {{0.001f, -10.0f, 0.0f}, {0.8f, 0.8f, 0.8f}, {1.0f, 0.0f}},
        {{-0.001f, 10.0f, 0.0f}, {0.8f, 0.8f, 0.8f}, {1.0f, 0.0f}},
        {{-0.001f, -10.0f, 0.0f}, {0.8f, 0.8f, 0.8f}, {1.0f, 0.0f}},
    };

    tileLineIndexX = {
        0, 2, 1,
        1, 2, 3
    };

    tileLineIndexY = {
        4, 5, 6,
        6, 5, 7
    };
}

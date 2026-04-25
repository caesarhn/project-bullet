#include <vulkan/init.h>

bool VulkanApplication::isWindowClosed(){
    return !glfwWindowShouldClose(window);
}

void VulkanApplication::prepLoop(){
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    int frame = 0;
    int animationFrame = 0;
    int walk_frame = 0;
    int animationWalk = 0;
    int idleDirection = 0;

    //random
    std::random_device rd;                 // sumber random
    std::mt19937 gen(rd());                // generator Mersenne Twister
    std::uniform_int_distribution<> dist(0, 4);
    std::uniform_int_distribution<> walks(0, 10);
    std::uniform_int_distribution<> xy(0, 1);
    float into = 0.0f;
    int x_or_y = xy(gen);
    int x = dist(gen);
    glm::vec3 translateRandom = glm::vec3(0.0f, 0.0f, 0.0f);
    int randomContainer;

    //world
    WorldLevel world;

    Walk walked_down{9};
    Walk walked_up{9};
    Walk walked_right{9};
    Walk walked_left{9};

    Walk idle{7};

    for(int x = 0; x < 100; x++){
        std::cout << x <<" "<< tileMaps[0].tiles[x] << std::endl; 
    }
}

void VulkanApplication::beginLoop(){
    glfwPollEvents();
    glfwGetCursorPos(window, &mouseX, &mouseY);
}

void VulkanApplication::endLoop(){
    updateUiData();
    drawFrame();
}
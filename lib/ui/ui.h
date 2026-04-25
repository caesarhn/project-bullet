
#pragma once
#include <constant.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>
#include <vector>
    
#include <iostream>
#include <stdio.h>

struct CharacterForGui{
    float textureIdx;
    float loc[2];
    float state;
};
    
class Gui {
private:
    float screenWidth;
    float screenHeight;
    VkDescriptorPool imguiPool;
    char text;
    bool is_focused = false;
    ImFont* gameFont;

    bool isUVMap = false;
    VkDescriptorSet uvMap;
    
public:
    bool debugCol = false;
    float charas[3];
    float mouseLoc[2];
    int *mainCharIdx;
    int *currentEvent;
    bool showTile;
    const char* items[4] = { "char 0", "char 1", "char 2", "D" };
    const char* eventOptions[4] = {"menu", "world", "battle", "inventory"};
    std::vector<int> tiles;
    int tileIndex;

    std::vector<bool> guiEnableWindows;
    std::vector<CharacterForGui> characterList;

    void createImGuiDescriptorPool(VkDevice device);
    void initImGui(GLFWwindow *window, VkInstance instance, VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, uint32_t queueFamily, VkRenderPass renderPass);
    void recordImGuiCommands(VkCommandBuffer commandBuffer);
    void setUVMap(VkDescriptorSet sampler);
    void beginUi();
    void endUi();
    void renderUI(float width, float height);
    void cleanupImGui(VkDevice device);
    void changeMainChar(int *idx);
    void updateTiles(std::vector<int> &tiles);
    void conversationUi();
    void battleUi();
    void inventoryUi();

};


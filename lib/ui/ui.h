
#pragma once
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

struct CharSkillsBattleUi{

};
    
class Gui {
private:
    VkDescriptorPool imguiPool;
    char text;
    bool is_focused = false;

    bool isUVMap = false;
    VkDescriptorSet uvMap;
    
public:
    
    float charas[3];
    float mouseLoc[2];
    int *mainCharIdx;
    const char* items[4] = { "char 0", "char 1", "char 2", "D" };

    std::vector<bool> guiEnableWindows;
    std::vector<CharacterForGui> characterList;

    void createImGuiDescriptorPool(VkDevice device);
    void initImGui(GLFWwindow *window, VkInstance instance, VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, uint32_t queueFamily, VkRenderPass renderPass);
    void recordImGuiCommands(VkCommandBuffer commandBuffer);
    void setUVMap(VkDescriptorSet sampler);
    void renderUI();
    void cleanupImGui(VkDevice device);
    void changeMainChar(int *idx);

};


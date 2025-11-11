
#ifdef __ANDROID__    // ← SETELAH vulkan.h
    #include <imgui.h>
    #include <backends/imgui_impl_vulkan.h>
    #include <backends/imgui_impl_android.h>
#else
    #pragma once
    #include <GLFW/glfw3.h>
    #include <imgui.h>
    #include <backends/imgui_impl_vulkan.h>
    #include <backends/imgui_impl_glfw.h>
    #include <vector>

#endif
    
#include <iostream>
#include <stdio.h>

struct CharacterForGui{
    float textureIdx;
    float loc[2];
    float state;
};
    
class Gui {
private:
    VkDescriptorPool imguiPool;
    char text;
    bool is_focused = false;

public:

    std::vector<bool> guiEnableWindows;
    std::vector<CharacterForGui> characterList;

    void createImGuiDescriptorPool(VkDevice device);
    #ifdef __ANDROID__
    void initImGui(ANativeWindow *window, VkInstance instance, VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, uint32_t queueFamily, VkRenderPass renderPass);
    #else
    void initImGui(GLFWwindow *window, VkInstance instance, VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, uint32_t queueFamily, VkRenderPass renderPass);
    #endif
    void recordImGuiCommands(VkCommandBuffer commandBuffer);
    void renderUI();
    void cleanupImGui(VkDevice device);
};


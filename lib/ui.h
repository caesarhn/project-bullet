#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>
#include <iostream>

class Gui {
private:
    VkDescriptorPool imguiPool;

public:
    void createImGuiDescriptorPool(VkDevice device);
    void initImGui(GLFWwindow *window, VkInstance instance, VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, uint32_t queueFamily, VkRenderPass renderPass);
    void recordImGuiCommands(VkCommandBuffer commandBuffer);
    void renderUI();
    void cleanupImGui(VkDevice device);
};


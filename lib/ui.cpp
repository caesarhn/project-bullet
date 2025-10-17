#include "ui.h"

void Gui::createImGuiDescriptorPool(VkDevice device){
        VkDescriptorPoolSize pool_sizes[] = {
        { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
    };

    VkDescriptorPoolCreateInfo pool_info{};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets = 1000;
    pool_info.poolSizeCount = (uint32_t)std::size(pool_sizes);
    pool_info.pPoolSizes = pool_sizes;

    if (vkCreateDescriptorPool(device, &pool_info, nullptr, &imguiPool) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create ImGui descriptor pool!");
    }
}

void Gui::initImGui(GLFWwindow *window, VkInstance instance, VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, uint32_t queueFamily, VkRenderPass renderPass){
    // 1. Buat context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.DisplaySize = ImVec2(static_cast<float>(800), static_cast<float>(600));
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Aktifkan navigasi keyboard

    // 2. Style ImGui (Opsional)
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForVulkan(window, true);

    // 3. Init Vulkan backend
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = instance;
    init_info.PhysicalDevice = physicalDevice;
    init_info.Device = device;
    // init_info.QueueFamily = queueFamily;
    init_info.Queue = queue;
    init_info.PipelineCache = VK_NULL_HANDLE;
    init_info.DescriptorPool = imguiPool;
    init_info.Subpass = 0;
    init_info.MinImageCount = 2;
    init_info.ImageCount = 2;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    init_info.RenderPass = renderPass;

    ImGui_ImplVulkan_Init(&init_info);
}

void Gui::recordImGuiCommands(VkCommandBuffer commandBuffer){
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
}

void Gui::renderUI(){
    ImGui_ImplVulkan_NewFrame();
    ImGui::NewFrame();
    // std::cout << "INIT IMGUI DEBUG" << std::endl;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Hello Vulkan ImGui");
    ImGui::Text("ImGui berjalan di Vulkan!");
    ImGui::End();

    ImGui::Render();
}

void Gui::cleanupImGui(VkDevice device){
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    vkDestroyDescriptorPool(device, imguiPool, nullptr);
    std::cout << "CLEAN UI DEBUG" << std::endl;
}
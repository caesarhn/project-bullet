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

    ImFontConfig font_cfg;
    font_cfg.RasterizerMultiply = 1.5f;

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.DisplaySize = ImVec2(static_cast<float>(2080), static_cast<float>(1080));
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Aktifkan navigasi keyboard
    io.Fonts->Flags |= ImFontAtlasFlags_NoBakedLines;
    io.Fonts->Build();

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

    //set font 
    io.Fonts->AddFontFromFileTTF("src/font/minecraftia.ttf", 16.0f); // ukuran kecil agar tetap tajam

    
    //initial gui variable
    guiEnableWindows.resize(1);
    guiEnableWindows[0] = false;
    characterList.resize(2);
    characterList[1].loc[0] = 3.0f;
    characterList[1].loc[1] = 0.0f;

    charas[0] = 0.0f;
    charas[1] = 0.0f;
    charas[2] = 0.0f;
}

void Gui::recordImGuiCommands(VkCommandBuffer commandBuffer){
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
}

void Gui::renderUI(){
    ImGui_ImplVulkan_NewFrame();
    ImGui::NewFrame();
    // std::cout << "INIT IMGUI DEBUG" << std::endl;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 300));
    ImGui::Begin("Hello Vulkan ImGui");
    ImGui::Text("characters");
    bool v = guiEnableWindows[0];
    if (ImGui::Checkbox("disable", &v)){
        guiEnableWindows[0] = v;        // simpan kembali hasilnya
    }
    ImGui::InputFloat3("loc", charas, "%.1f");

    bool uv = isUVMap;
    if (ImGui::Checkbox("uv map", &uv)){
        isUVMap = uv;        // simpan kembali hasilnya
    }
    ImGui::Columns(2);
    ImGui::InputFloat("x: ", &mouseLoc[0]); ImGui::NextColumn();
    ImGui::InputFloat("y: ", &mouseLoc[1]);

    ImGui::Combo("Select Key", mainCharIdx, items, IM_ARRAYSIZE(items));

    ImGui::End();

    ImGui::Render();
}

void Gui::setUVMap(VkDescriptorSet sampler){
    uvMap = sampler;
}

void Gui::cleanupImGui(VkDevice device){
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    vkDestroyDescriptorPool(device, imguiPool, nullptr);
    std::cout << "CLEAN UI DEBUG" << std::endl;
}

void Gui::changeMainChar(int *idx){

}

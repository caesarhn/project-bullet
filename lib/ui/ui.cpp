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
    font_cfg.RasterizerMultiply = 1.0f;

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.DisplaySize = ImVec2(static_cast<float>(2080), static_cast<float>(1080));
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Aktifkan navigasi keyboard
    io.Fonts->Flags |= ImFontAtlasFlags_NoBakedLines;
    io.Fonts->Build();

    io.Fonts->AddFontDefault();
    gameFont = io.Fonts->AddFontFromFileTTF("src/font/minecraftia.ttf", 18.5f, NULL, io.Fonts->GetGlyphRangesJapanese());

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

    tiles.resize(100);
    currentEvent = new int(0);
}

void Gui::recordImGuiCommands(VkCommandBuffer commandBuffer){
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
}

void Gui::beginUi(){
    ImGui_ImplVulkan_NewFrame();
    ImGui::NewFrame();
}

void Gui::endUi(){
    ImGui::Render();
}

void Gui::renderUI(float width, float height){
    screenWidth = width;
    screenHeight = height;

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
    ImGui::Checkbox("debug_col", &debugCol);
    
    ImGui::InputFloat3("loc", charas, "%.1f");
    
    bool uv = isUVMap;
    if (ImGui::Checkbox("uv map", &uv)){
        isUVMap = uv;        // simpan kembali hasilnya
    }
    
    ImGui::PushFont(gameFont);
    ImGui::Columns(2);
    ImGui::InputFloat("x: ", &mouseLoc[0]); 
    ImGui::NextColumn();
    ImGui::InputFloat("y: ", &mouseLoc[1]);
    ImGui::PopFont();
    
    ImGui::Columns(1);
    ImGui::Combo("Select Key", mainCharIdx, items, IM_ARRAYSIZE(items));
    ImGui::Combo("Choose Event", currentEvent, eventOptions, IM_ARRAYSIZE(eventOptions));
    if (ImGui::Checkbox("show tile", &showTile)){
        // simpan kembali hasilnya
    }
    
    ImGui::Columns(2);
    ImGui::InputInt("idx: ", &tileIndex);
    ImGui::InputInt("value: ", &tiles[tileIndex]);
    
    ImGui::End();
    
    if(*currentEvent == EVENT_WORLD){
        std::cout << "DEBUG MAIN UI" << std::endl;
        conversationUi();
    }
    else if(*currentEvent == EVENT_BATTLE){
        battleUi();
    }
    else if(*currentEvent == EVENT_INVENTORY){
        inventoryUi();
    }
    
    ImGui::Render();
}

void Gui::conversationUi(){
    // Dapatkan viewport dan work area
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize 
                    | ImGuiWindowFlags_NoMove
                    | ImGuiWindowFlags_NoBringToFrontOnFocus
                    | ImGuiWindowFlags_NoCollapse;

    // Terapkan posisi dan ukuran
    ImGui::SetNextWindowPos(ImVec2(20.0f, (screenHeight - (screenHeight / 4) - 20.0f)));
    ImGui::SetNextWindowSize(ImVec2((screenWidth - 40.0f), (screenHeight / 4)));

    ImGui::PushFont(gameFont);
    // ImGui::SetNextWindowPos(ImVec2(0, 0));
    // ImGui::SetNextWindowSize(ImVec2(250, 300));
    ImGui::Begin("Character Name", nullptr, flags);

    ImGui::Text("This is an example of character conversations..");
    ImGui::Text("  Posisi (Pos):      (%.1f, %.1f)", viewport->WorkPos.x, viewport->WorkPos.y);
    ImGui::Text("  Ukuran (Size):     (%.1f, %.1f)", viewport->Size.x, viewport->Size.y);
    ImGui::Text("  Ukuran (Size):     (%.1f, %.1f)", screenWidth, screenHeight);

    ImGui::PopFont();
    ImGui::End();
}

void Gui::battleUi(){

    // Terapkan posisi dan ukuran
    ImGui::SetNextWindowPos(ImVec2(20.0f, (screenHeight - (screenHeight / 4) - 20.0f)));
    ImGui::SetNextWindowSize(ImVec2((screenWidth - 40.0f), (screenHeight / 4)));
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar 
                       | ImGuiWindowFlags_NoResize 
                       | ImGuiWindowFlags_NoMove
                       | ImGuiWindowFlags_NoBringToFrontOnFocus
                       | ImGuiWindowFlags_NoCollapse;

    ImGui::PushFont(gameFont);

    ImGui::Begin("Battle", nullptr, flags);

    ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); // Warna saat mouse di atasnya (hijau terang)
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.0f, 0.5f, 0.0f, 1.0f)); // Warna saat ditekan (hijau gelap)
    
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.0f, 10.0f));

    if (ImGui::Button("Tombol Hijau Kustom")) {
        // Logika tombol
    }

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();

    ImGui::PopFont();
    ImGui::End();
}

void Gui::inventoryUi(){
        ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize 
                    | ImGuiWindowFlags_NoMove
                    | ImGuiWindowFlags_NoBringToFrontOnFocus
                    | ImGuiWindowFlags_NoCollapse
                    | ImGuiWindowFlags_NoTitleBar;

    // Terapkan posisi dan ukuran
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2((screenWidth), (screenHeight)));

    ImGui::PushFont(gameFont);
    ImGui::Begin("Inventory", nullptr, flags);

    ImGui::Text("This is an example of character conversations..");
    ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 7.0f);
    ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.1f, 0.1f, 0.1f, 0.1f));
    if (ImGui::BeginTabBar("InventoryTab")){
        if (ImGui::BeginTabItem("Items")) 
        {
            ImGui::Text("Ini adalah konten di dalam tab pertama.");
            ImGui::Button("Klik Saya");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Character")) 
        {
            ImGui::Text("Ini adalah konten yang berbeda di tab kedua.");
            static float f = 0.5f;
            ImGui::SliderFloat("Slider", &f, 0.0f, 1.0f);
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(1);

    ImGui::PopFont();
    ImGui::End();
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

void Gui::updateTiles(std::vector<int> &Tiles){
    for(int x = 0; x < 100; x++){
        Tiles[x] = tiles[x];
    }
}

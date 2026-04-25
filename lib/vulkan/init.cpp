#include <vulkan/init.h>

VkResult VulkanApplication::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    std::cout << "Debug Messenger create.." << std::endl;
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void VulkanApplication::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}
#ifdef __ANDROID__
void VulkanApplication::setAndroidWindow(ANativeWindow *win){
    window = win;
}
#else
#endif

void VulkanApplication::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}
void VulkanApplication::initVulkan(){
    initVariables();
    initUbo();
    initPushConstant();
    initTileMaps();
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createSwapChain();
    createImageViews();
    createRenderPass();
    
    createDescriptorSetLayout();
    createBattleSamplerDescriptorSetLayout();

    createGraphicsPipeline();
    createGraphicsPipelineDebug();
    createGraphicsPipelineBattle();
    createCommandPool();
    createDepthResources();
    createFramebuffers();
    
    for(int i = 0; i < textureAssets.size(); i++){
        createTextureImages(textureAssets[i].c_str());
    }

    for(int i = 0; i < characterAssets.size(); i++){
        createCharacterTextureImages(characterAssets[i].c_str());
    }
    
    createTextureImageViews();
    createTextureSamplers();
    
    createTextureImage();
    createTextureImageView();
    createTextureSampler();

    for(int i = 0; i < battleEnemyAssets.size(); i++){
        createTexturesImages(battleEnemyImages, battleEnemyImageMemorys, battleEnemyAssets[i].c_str());
    }
    createTexturesImagesViews(battleEnemyImages, battleEnemyImageViews);
    createTexturesSamplers(battleEnemySamplers, battleEnemyImages);
    
    for(int i = 0; i < battleEffectAssets.size(); i++){
        DEBUG_LOG(i);
        createTexturesImages(battleEffectImages, battleEffectImageMemorys, battleEffectAssets[i].c_str());
        DEBUG_LOG("FUNTION");
    }
    createTexturesImagesViews(battleEffectImages, battleEffectImageViews);
    createTexturesSamplers(battleEffectSamplers, battleEffectImages);
    
    // for(int i = 0; i < objectPool.size(); i++){
        //     createVertexBuffer(objectPool[i].vertices, vertexBufferPool[i], vertexBufferMemoryPool[i]);
        // }
        // createVertexBuffer(vertices, vertexBuffer, vertexBufferMemory);
    createVertexBufferHehe();
    createVertexBuffer(vertices2, vertexBuffer1, vertexBufferMemory1);
    createVertexBuffer(tileLines, vertexBufferTileLine, vertexBufferMemoryTileLine);
    createIndexBuffers();
    createIndexBuffer(tileLineIndexX, indexBufferTileLines, indexBufferMemoryTileLines);
    createUniformBuffers();
    createStorageBuffers(tileMaps, tileMapStorageBuffers, tileMapStorageBuffersMemory, tileMapStorageBuffersMapped);
    createDescriptorPool();
    createDescriptorSets();
    createCommandBuffers();
    createSyncObjects();

    gui.createImGuiDescriptorPool(device);
    gui.initImGui(window, instance, device, physicalDevice, graphicsQueue, 0, renderPass);
    gui.mainCharIdx = &indexMainChar;
}

void VulkanApplication::createVertexBufferHehe() {
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

    copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void VulkanApplication::updateUiData(){
    // characters[1].set_and_binding = glm::vec2(1.0f, gui.characterList[1].textureIdx);
    lockgui = gui.guiEnableWindows[0];
    gui.mouseLoc[0] = mouseWorld.x;
    gui.mouseLoc[1] = mouseWorld.y;
    if(lockgui == false){
        uboCharacter.model = glm::translate(glm::mat4(1.0f), glm::vec3(gui.charas[0], gui.charas[1], gui.charas[2]));
    }
    gui.updateTiles(tileMaps[0].tiles);

    currentEvent = *gui.currentEvent;
}

void VulkanApplication::createInstance(){
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void VulkanApplication::setupDebugMessenger(){
    if (!enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void VulkanApplication::createSurface(){
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}
void VulkanApplication::pickPhysicalDevice(){
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}
void VulkanApplication::createLogicalDevice(){
    std::cout << "creating logical devices" << std::endl;
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}
void VulkanApplication::createSwapChain(){
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent = extent;
}
void VulkanApplication::createImageViews(){
    swapChainImageViews.resize(swapChainImages.size());

    for (uint32_t i = 0; i < swapChainImages.size(); i++) {
        swapChainImageViews[i] = createImageView(swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
    }
}
void VulkanApplication::createRenderPass(){
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentDescription depthAttachment{};
    depthAttachment.format = findDepthFormat();
    depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthAttachmentRef{};
    depthAttachmentRef.attachment = 1;
    depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
    subpass.pDepthStencilAttachment = &depthAttachmentRef;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }
}
void VulkanApplication::createDescriptorSetLayout(){

    //Uniform Character
    VkDescriptorSetLayoutBinding uboLayoutCharacter{};
    uboLayoutCharacter.binding = 0;
    uboLayoutCharacter.descriptorCount = 1;
    uboLayoutCharacter.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutCharacter.pImmutableSamplers = nullptr;
    uboLayoutCharacter.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    
    std::array<VkDescriptorSetLayoutBinding,1> bindingCharacter = {uboLayoutCharacter};
    VkDescriptorSetLayoutCreateInfo characterLayoutInfo{};
    characterLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    characterLayoutInfo.bindingCount = static_cast<uint32_t>(bindingCharacter.size());
    characterLayoutInfo.pBindings = bindingCharacter.data();

    //Uniform Global
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.pImmutableSamplers = nullptr;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    std::array<VkDescriptorSetLayoutBinding, 1> bindings = {uboLayoutBinding};
    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();

    //uniform Tile
    VkDescriptorSetLayoutBinding uboLayoutBindingTile{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.pImmutableSamplers = nullptr;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    std::array<VkDescriptorSetLayoutBinding,1> bindingTile = {uboLayoutBindingTile};
    VkDescriptorSetLayoutCreateInfo tileLayoutInfo{};
    tileLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    tileLayoutInfo.bindingCount = static_cast<uint32_t>(bindingTile.size());
    tileLayoutInfo.pBindings = bindingTile.data();

    VkDescriptorSetLayoutBinding tileMapStorageLayoutBinding{};
    tileMapStorageLayoutBinding.binding = 0;
    tileMapStorageLayoutBinding.descriptorCount = 1;
    tileMapStorageLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    tileMapStorageLayoutBinding.pImmutableSamplers = nullptr;
    tileMapStorageLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    std::array<VkDescriptorSetLayoutBinding,1> tileMapBinding = {tileMapStorageLayoutBinding};
    VkDescriptorSetLayoutCreateInfo tileMapLayoutInfo{};
    tileMapLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    tileMapLayoutInfo.bindingCount = static_cast<uint32_t>(tileMapBinding.size());
    tileMapLayoutInfo.pBindings = tileMapBinding.data();

    //Uniform Character Sampler
    // std::vector<VkDescriptorSetLayoutBinding> characterAnimateLayoutBinding (characterAsset.size());
    // for(int i = 0; i < characterAsset.size(); i++){
    //     characterAnimateLayoutBinding[i].binding = i;
    //     characterAnimateLayoutBinding[i].descriptorCount = 1;
    //     characterAnimateLayoutBinding[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    //     characterAnimateLayoutBinding[i].pImmutableSamplers = nullptr;
    //     characterAnimateLayoutBinding[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    // }
    VkDescriptorSetLayoutBinding characterSamplerLayoutBinding{};
    characterSamplerLayoutBinding.binding = 0;
    characterSamplerLayoutBinding.descriptorCount = static_cast<uint32_t>(characterAssets.size());
    characterSamplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    characterSamplerLayoutBinding.pImmutableSamplers = nullptr;
    characterSamplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    
    // std::vector<VkDescriptorSetLayoutBinding> characterSamplerLayoutBindings(characterImages.size());
    VkDescriptorSetLayoutCreateInfo characterAnimateLayoutInfo{};
    characterAnimateLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    characterAnimateLayoutInfo.bindingCount = 1;//static_cast<uint32_t>(characterSamplerLayoutBindings.size());
    characterAnimateLayoutInfo.pBindings = &characterSamplerLayoutBinding;

    //Create All Descroptorset Layout
    if (vkCreateDescriptorSetLayout(device, &characterLayoutInfo, nullptr, &descriptorSetLayoutCharacter) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
    if (vkCreateDescriptorSetLayout(device, &characterAnimateLayoutInfo, nullptr, &descriptorSetLayoutCharacterSampler) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
    if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
    if (vkCreateDescriptorSetLayout(device, &tileMapLayoutInfo, nullptr, &descriptorSetLayoutTileMap) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

void VulkanApplication::createCommandPool(){
    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics command pool!");
    }
}
void VulkanApplication::createDepthResources(){
    VkFormat depthFormat = findDepthFormat();

    createImage(swapChainExtent.width, swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
    depthImageView = createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}
void VulkanApplication::createDescriptorSets() {
    //SET 0
    std::vector<VkDescriptorSetLayout> layouts {
        descriptorSetLayout, descriptorSetLayout
    };
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(layouts.size());
    allocInfo.pSetLayouts = layouts.data();
    
    descriptorSets.resize((MAX_FRAMES_IN_FLIGHT));
    if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    //SET 1
    //character + object
    std::vector<VkDescriptorSetLayout> characterLayouts(MAX_FRAMES_IN_FLIGHT * entities.size());
    for(int i = 0; i < MAX_FRAMES_IN_FLIGHT * entities.size(); i++){
        characterLayouts[i] = descriptorSetLayoutCharacter;
    }

    VkDescriptorSetAllocateInfo allocInfoCharacter{};
    allocInfoCharacter.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfoCharacter.descriptorPool = descriptorPool;
    allocInfoCharacter.descriptorSetCount = static_cast<uint32_t>(characterLayouts.size());
    allocInfoCharacter.pSetLayouts = characterLayouts.data();
    
    descriptorSetsCharacter.resize((MAX_FRAMES_IN_FLIGHT * entities.size()));
    if (vkAllocateDescriptorSets(device, &allocInfoCharacter, descriptorSetsCharacter.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets character!");
    }

    //SET 2
    std::vector<VkDescriptorSetLayout> characterSamplerLayout {
        descriptorSetLayoutCharacterSampler, descriptorSetLayoutCharacterSampler
    };

    VkDescriptorSetAllocateInfo allocInfoCharacterSampler{};
    allocInfoCharacterSampler.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfoCharacterSampler.descriptorPool = descriptorPool;
    allocInfoCharacterSampler.descriptorSetCount = static_cast<uint32_t>(characterSamplerLayout.size());
    allocInfoCharacterSampler.pSetLayouts = characterSamplerLayout.data();

    descriptorSetsCharacterSampler.resize(MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(device, &allocInfoCharacterSampler, descriptorSetsCharacterSampler.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets character sampler!");
    }

    //SET 3
    std::vector<VkDescriptorSetLayout> tileMapLayout {
        descriptorSetLayoutTileMap, descriptorSetLayoutTileMap,
    };
    
    VkDescriptorSetAllocateInfo allocInfoTileMap{};
    allocInfoTileMap.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfoTileMap.descriptorPool = descriptorPool;
    allocInfoTileMap.descriptorSetCount = static_cast<uint32_t>(tileMapLayout.size());
    allocInfoTileMap.pSetLayouts = tileMapLayout.data();
    
    descriptorSetsTileMap.resize(MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(device, &allocInfoTileMap, descriptorSetsTileMap.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets tilemmap!");
    }

    //SET BATTLE ENEMY 
    std::vector<VkDescriptorSetLayout> battleSamplerLayout{
        descriptorSetLayoutBattleSampler, descriptorSetLayoutBattleSampler,
    };
    VkDescriptorSetAllocateInfo allocInfoBattleEnemySampler{};
    allocInfoBattleEnemySampler.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfoBattleEnemySampler.descriptorPool = descriptorPool;
    allocInfoBattleEnemySampler.descriptorSetCount = static_cast<uint32_t>(battleSamplerLayout.size());
    allocInfoBattleEnemySampler.pSetLayouts = battleSamplerLayout.data();

    descriptorSetsBattleSampler.resize(MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(device, &allocInfoBattleEnemySampler, descriptorSetsBattleSampler.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets battle enemy sampler!");
    }
    
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        //SET 0 per frame
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);
        
        //SET 1 per frame
        std::vector<VkDescriptorBufferInfo> characterInfo(entities.size());
        for(int s = 0; s < entities.size(); s++){
            characterInfo[s].buffer = entityUniformBuffers[(s*MAX_FRAMES_IN_FLIGHT)+i];
            characterInfo[s].offset = 0;
            characterInfo[s].range = sizeof(UniformBufferObjectEntity);
        } 
        
        //SET 2 per frame
        std::vector<VkDescriptorImageInfo> characterImageInfos(characterImages.size());
        for (size_t x = 0; x < characterImages.size(); x++){
            characterImageInfos[x].sampler = characterSamplers[x];
            characterImageInfos[x].imageView = characterImageViews[x];
            characterImageInfos[x].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }
        
        DEBUG_LOG("DESCRIPTOR SETS");
        //SET 3 per frame
        std::vector<VkDescriptorBufferInfo> tileMapInfos(tileMaps.size());
        for (size_t x = 0; x < tileMaps.size(); x++){
            tileMapInfos[x].buffer = tileMapStorageBuffers[(x * MAX_FRAMES_IN_FLIGHT) + i];
            tileMapInfos[x].offset = 0;
            tileMapInfos[x].range = VK_WHOLE_SIZE;
        }

        //SET Battle Enemy sampler
        std::vector<VkDescriptorImageInfo> battleEnemyImagesInfos(battleEnemyImages.size());
        for (size_t x = 0; x < battleEnemyImages.size(); x++){
            battleEnemyImagesInfos[x].sampler = battleEnemySamplers[x];
            battleEnemyImagesInfos[x].imageView = battleEnemyImageViews[x];
            battleEnemyImagesInfos[x].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }

        //SET Battle Effect sampler
        std::vector<VkDescriptorImageInfo> battleEffectImagesInfos(battleEffectImages.size());
        for (size_t x = 0; x < battleEffectImages.size(); x++){
            battleEffectImagesInfos[x].sampler = battleEffectSamplers[x];
            battleEffectImagesInfos[x].imageView = battleEffectImageViews[x];
            battleEffectImagesInfos[x].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }
        
        std::vector<VkWriteDescriptorSet> descriptorWrites(1 + entities.size() + characterImages.size() + tileMaps.size() + battleEnemyImages.size() + battleEffectImages.size());
        
        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;
        
        for(int s = 0; s < entities.size(); s++){
            descriptorWrites[1+s].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1+s].dstSet = descriptorSetsCharacter[(s*MAX_FRAMES_IN_FLIGHT)+i];
            descriptorWrites[1+s].dstBinding = 0;
            descriptorWrites[1+s].dstArrayElement = 0;
            descriptorWrites[1+s].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites[1+s].descriptorCount = 1;
            descriptorWrites[1+s].pBufferInfo = &characterInfo[s];
        }
        
        for(int s = 0; s < characterImages.size(); s++){
            descriptorWrites[1+entities.size()+s].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1+entities.size()+s].dstSet = descriptorSetsCharacterSampler[i];
            descriptorWrites[1+entities.size()+s].dstBinding = 0;
            descriptorWrites[1+entities.size()+s].dstArrayElement = s;
            descriptorWrites[1+entities.size()+s].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1+entities.size()+s].descriptorCount = 1;
            descriptorWrites[1+entities.size()+s].pImageInfo = &characterImageInfos[s];
        }

        for(int s = 0; s < tileMaps.size(); s++){
            descriptorWrites[1+entities.size()+characterImages.size()+s].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1+entities.size()+characterImages.size()+s].dstSet = descriptorSetsTileMap[i];
            descriptorWrites[1+entities.size()+characterImages.size()+s].dstBinding = 0;
            descriptorWrites[1+entities.size()+characterImages.size()+s].dstArrayElement = 0;
            descriptorWrites[1+entities.size()+characterImages.size()+s].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            descriptorWrites[1+entities.size()+characterImages.size()+s].descriptorCount = 1;
            descriptorWrites[1+entities.size()+characterImages.size()+s].pBufferInfo = &tileMapInfos[s];
        }

        for(int s = 0; s < battleEnemyImages.size(); s++){
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+s].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+s].dstSet = descriptorSetsBattleSampler[i];
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+s].dstBinding = 0;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+s].dstArrayElement = s;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+s].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+s].descriptorCount = 1;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+s].pImageInfo = &battleEnemyImagesInfos[s];
        }

        for(int s = 0; s < battleEffectImages.size(); s++){
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+battleEnemyImages.size()+s].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+battleEnemyImages.size()+s].dstSet = descriptorSetsBattleSampler[i];
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+battleEnemyImages.size()+s].dstBinding = 1;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+battleEnemyImages.size()+s].dstArrayElement = s;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+battleEnemyImages.size()+s].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+battleEnemyImages.size()+s].descriptorCount = 1;
            descriptorWrites[1+entities.size()+characterImages.size()+tileMaps.size()+battleEnemyImages.size()+s].pImageInfo = &battleEffectImagesInfos[s];
        }
        
        vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }

}

void VulkanApplication::createSyncObjects() {
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

void VulkanApplication::cleanupSwapChain() {
    vkDestroyImageView(device, depthImageView, nullptr);
    vkDestroyImage(device, depthImage, nullptr);
    vkFreeMemory(device, depthImageMemory, nullptr);

    for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }

    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(device, imageView, nullptr);
    }

    vkDestroySwapchainKHR(device, swapChain, nullptr);
}

void VulkanApplication::cleanup() {
    gui.cleanupImGui(device);
    cleanupSwapChain();

    vkDestroyPipeline(device, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    vkDestroyPipeline(device, graphicsPipelineDebug, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayoutDebug, nullptr);
    vkDestroyPipeline(device, graphicsPipelineBattle, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayoutBattle, nullptr);
    vkDestroyRenderPass(device, renderPass, nullptr);

    for (size_t i = 0; i < uniformBuffers.size(); i++) {
        vkDestroyBuffer(device, uniformBuffers[i], nullptr);
        vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
    }

    for(size_t i = 0; i < tileMapStorageBuffers.size(); i++){
        vkDestroyBuffer(device, tileMapStorageBuffers[i], nullptr);
        vkFreeMemory(device, tileMapStorageBuffersMemory[i], nullptr);
    }
    
    for (size_t i = 0; i < entityUniformBuffers.size(); i++) {
        vkDestroyBuffer(device, entityUniformBuffers[i], nullptr);
        vkFreeMemory(device, entityUniformBuffersMemory[i], nullptr);
    }

    // for (size_t i = 0; i < tileUniformBuffers.size(); i++){
    //     vkDestroyBuffer(device, tileUniformBuffers[i], nullptr);
    //     vkFreeMemory(device, tileUniformBuffersMemory[i], nullptr);
    // }

    DEBUG_LOG("CLEANUP 1");
    vkDestroyDescriptorPool(device, descriptorPool, nullptr);

    for (int i = 0; i < textureImages.size(); i++) {
        vkDestroySampler(device, textureSamplers[i], nullptr);
        vkDestroyImageView(device, textureImageViews[i], nullptr);
        vkDestroyImage(device, textureImages[i], nullptr);
        vkFreeMemory(device, textureImageMemorys[i], nullptr);
    }
    vkDestroySampler(device, textureSampler, nullptr);
    vkDestroyImageView(device, textureImageView, nullptr);

    vkDestroyImage(device, textureImage, nullptr);
    vkFreeMemory(device, textureImageMemory, nullptr);

    for (int i = 0; i < characterImages.size(); i++) {
        vkDestroySampler(device, characterSamplers[i], nullptr);
        vkDestroyImageView(device, characterImageViews[i], nullptr);
        vkDestroyImage(device, characterImages[i], nullptr);
        vkFreeMemory(device, characterImageMemorys[i], nullptr);
    }

    for (int i = 0; i < battleEnemyImages.size(); i++) {
        vkDestroySampler(device, battleEnemySamplers[i], nullptr);
        vkDestroyImageView(device, battleEnemyImageViews[i], nullptr);
        vkDestroyImage(device, battleEnemyImages[i], nullptr);
        vkFreeMemory(device, battleEnemyImageMemorys[i], nullptr);
    }

    for (int i = 0; i < battleEffectImages.size(); i++) {
        vkDestroySampler(device, battleEffectSamplers[i], nullptr);
        vkDestroyImageView(device, battleEffectImageViews[i], nullptr);
        vkDestroyImage(device, battleEffectImages[i], nullptr);
        vkFreeMemory(device, battleEffectImageMemorys[i], nullptr);
    }

    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    vkDestroyDescriptorSetLayout(device, descriptorSetLayoutCharacter, nullptr);
    vkDestroyDescriptorSetLayout(device, descriptorSetLayoutCharacterSampler, nullptr);
    vkDestroyDescriptorSetLayout(device, descriptorSetLayoutTileMap, nullptr);
    vkDestroyDescriptorSetLayout(device, descriptorSetLayoutBattleSampler, nullptr);

    vkDestroyBuffer(device, indexBuffer, nullptr);
    vkFreeMemory(device, indexBufferMemory, nullptr);

    vkDestroyBuffer(device, indexBufferTileLines, nullptr);
    vkFreeMemory(device, indexBufferMemoryTileLines, nullptr);

    vkDestroyBuffer(device, vertexBuffer, nullptr);
    vkFreeMemory(device, vertexBufferMemory, nullptr);

    vkDestroyBuffer(device, vertexBuffer1, nullptr);
    vkFreeMemory(device, vertexBufferMemory1, nullptr);

    vkDestroyBuffer(device, vertexBufferTileLine, nullptr);
    vkFreeMemory(device, vertexBufferMemoryTileLine, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(device, inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(device, commandPool, nullptr);

    vkDestroyDevice(device, nullptr);

    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }

    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void VulkanApplication::recreateSwapChain() {
    int width = 0, height = 0;

    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(device);

    cleanupSwapChain();

    createSwapChain();
    createImageViews();
    createDepthResources();
    createFramebuffers();
}
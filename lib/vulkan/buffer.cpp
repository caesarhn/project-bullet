#include <vulkan/init.h>

void VulkanApplication::createFramebuffers(){
    swapChainFramebuffers.resize(swapChainImageViews.size());

    for (size_t i = 0; i < swapChainImageViews.size(); i++) {
        std::array<VkImageView, 2> attachments = {
            swapChainImageViews[i],
            depthImageView
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = swapChainExtent.width;
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void VulkanApplication::createVertexBuffer(std::vector<Vertex> Vertex, VkBuffer &VBuffer, VkDeviceMemory &VBMemory) {
    std::cout << "DEBUG VertexBuffer" << std::endl;
    VkDeviceSize bufferSize = sizeof(Vertex[0]) * Vertex.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, Vertex.data(), (size_t)(bufferSize));
    vkUnmapMemory(device, stagingBufferMemory);

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VBuffer, VBMemory);

    copyBuffer(stagingBuffer, VBuffer, bufferSize);

    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void VulkanApplication::createIndexBuffer() {
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t) bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    copyBuffer(stagingBuffer, indexBuffer, bufferSize);

    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void VulkanApplication::createUniformBuffers() {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);
    VkDeviceSize bufferSizeCharacter = sizeof(UniformBufferObjectCharacter);
    VkDeviceSize bufferSizeTile = sizeof(UniformBufferObjectTile);

    int charactersCount = characters.size();

    uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    characterUniformBuffers.resize(MAX_FRAMES_IN_FLIGHT * charactersCount);
    characterUniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT * charactersCount);
    characterUniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT * charactersCount);

    tileUniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    tileUniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    tileUniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

        vkMapMemory(device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
    }

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT * charactersCount; i++) {
        createBuffer(bufferSizeCharacter, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, characterUniformBuffers[i], characterUniformBuffersMemory[i]);

        vkMapMemory(device, characterUniformBuffersMemory[i], 0, bufferSizeCharacter, 0, &characterUniformBuffersMapped[i]);
    }

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        createBuffer(bufferSizeTile, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, tileUniformBuffers[i], tileUniformBuffersMemory[i]);

        vkMapMemory(device, tileUniformBuffersMemory[i], 0, bufferSizeTile, 0, &tileUniformBuffersMapped[i]);
    }
}

void VulkanApplication::createCommandBuffers() {
    commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

    if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void VulkanApplication::initUbo(){
    ubo.view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 2.0f), // Posisi kamera (x, y, z)
        glm::vec3(0.0f, 0.0f, 0.0f), // Arah kamera (target)
        glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector (ke atas)
    );
    ubo.projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    // ubo.projection[2][2] = -0.020002f;
    // ubo.projection[3][2] = -1.002002f;
    // ubo.projection = glm::perspective(
    //     glm::radians(45.0f),   // FOV
    //     WIDTH / (float)HEIGHT, // aspect ratio
    //     0.1f,                  // near
    //     100.0f                 // far
    // );
    ubo.projection[1][1] *= -1;

    uboCharacter.model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    characters.resize(20);
    for(int i = 0; i < characters.size(); i++){
        charactersAttribute.emplace_back(7, 9);
        charactersAttribute[i].isRender = false;
    }

    characters[0] = uboCharacter;
    characters[1] = uboCharacter;
    characters[2] = uboCharacter;

    for(int i = 3; i < 20; i++){
        characters[i] = uboCharacter;
    }
}
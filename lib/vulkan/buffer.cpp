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

void VulkanApplication::createVertexBuffer(std::vector<Vertex> &vertices_local, VkBuffer &vertexBuffer_local, VkDeviceMemory &vertexBufferMemory_local) {
    DEBUG_LOG("Vertex Buffer");
    VkDeviceSize bufferSize = sizeof(vertices_local[0]) * vertices_local.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices_local.data(), (size_t)(bufferSize));
    vkUnmapMemory(device, stagingBufferMemory);

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer_local, vertexBufferMemory_local);

    copyBuffer(stagingBuffer, vertexBuffer_local, bufferSize);

    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void VulkanApplication::createIndexBuffers() {
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

void VulkanApplication::createIndexBuffer(std::vector<uint16_t> &indices_local, VkBuffer &indexBuffer_local, VkDeviceMemory &indexBufferMemory_local) {
    VkDeviceSize bufferSize = sizeof(indices_local[0]) * indices_local.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices_local.data(), (size_t) bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer_local, indexBufferMemory_local);

    copyBuffer(stagingBuffer, indexBuffer_local, bufferSize);

    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void VulkanApplication::createUniformBuffers() {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);
    VkDeviceSize bufferSizeCharacter = sizeof(UniformBufferObjectEntity);
    VkDeviceSize bufferSizeObject = bufferSizeCharacter;

    int entityCount = entities.size();

    uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    entityUniformBuffers.resize(MAX_FRAMES_IN_FLIGHT * entityCount);
    entityUniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT * entityCount);
    entityUniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT * entityCount);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

        vkMapMemory(device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
    }

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT * entityCount; i++) {
        createBuffer(bufferSizeCharacter, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, entityUniformBuffers[i], entityUniformBuffersMemory[i]);

        vkMapMemory(device, entityUniformBuffersMemory[i], 0, bufferSizeCharacter, 0, &entityUniformBuffersMapped[i]);
    }
}

void VulkanApplication::createStorageBuffers(std::vector<TileMap> &tiles, std::vector<VkBuffer> &buffer, std::vector<VkDeviceMemory> &bufferMemory, std::vector<void*> &bufferMapped) {
    // VkDeviceSize bufferSize = tiles[t].tiles.size();

    buffer.resize(MAX_FRAMES_IN_FLIGHT * tiles.size());
    bufferMemory.resize(MAX_FRAMES_IN_FLIGHT * tiles.size());
    bufferMapped.resize(MAX_FRAMES_IN_FLIGHT * tiles.size());
    
    for(int t = 0; t < tiles.size(); t++){
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            VkDeviceSize bufferSize = tiles[t].tiles.size() * sizeof(int);
            DEBUG_LOG(i);
            DEBUG_LOG(bufferSize);
            int index = (t * MAX_FRAMES_IN_FLIGHT + i);
            createBuffer(bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer[index], bufferMemory[index]);
    
            vkMapMemory(device, bufferMemory[index], 0, bufferSize, 0, &bufferMapped[index]);
        }
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
        glm::vec3(0.0f, 0.0f, 5.0f), // Posisi kamera (x, y, z)
        glm::vec3(0.0f, 0.0f, 0.0f), // Arah kamera (target)
        glm::vec3(0.0f, -1.0f, 0.0f)  // Up vector (ke atas)
    );
    ubo.projection = glm::ortho(-8.0f, 8.0f, 4.5f, -4.5f, 0.1f, 10.0f);
    // ubo.projection[1][1] *= -1.0f;

    uboCharacter.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    uboCharacter.animationDetail = glm::ivec4(4, 8, 0, 0);
    uboCharacter.controlAnimation = glm::ivec4(0, 0, 0, 0);
    uboCharacter.samplerIndex = glm::ivec4(0, 1, 2, 0);
    
    initCharacters();
}

void VulkanApplication::initPushConstant(){
    battlePushConstant.animationIdx = glm::ivec4(0);
}
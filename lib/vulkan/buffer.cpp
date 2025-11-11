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
        memcpy(data, Vertex.data(), (size_t) bufferSize);
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

    int charactersCount = characters.size();

    uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT * charactersCount + 2);
    uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT * charactersCount + 2);
    uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT * charactersCount + 2);

    characterUniformBuffers.resize(MAX_FRAMES_IN_FLIGHT * charactersCount);
    characterUniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT * charactersCount);
    characterUniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT * charactersCount);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT * charactersCount + 2; i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

        vkMapMemory(device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
    }

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT * charactersCount; i++) {
        createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, characterUniformBuffers[i], characterUniformBuffersMemory[i]);

        vkMapMemory(device, characterUniformBuffersMemory[i], 0, bufferSize, 0, &characterUniformBuffersMapped[i]);
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
    ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f), // Posisi kamera (x, y, z)
        glm::vec3(0.0f, 0.0f, 0.0f), // Arah kamera (target)
        glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector (ke atas)
    );
    ubo.proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    ubo.proj[1][1] *= -1;

    ubo2.model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo2.view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f), // Posisi kamera (x, y, z)
        glm::vec3(0.0f, 0.0f, 0.0f), // Arah kamera (target)
        glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector (ke atas)
    );
    ubo2.proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    ubo2.proj[1][1] *= -1;
    // ubo2.model = glm::translate(ubo2.model, glm::vec3(-3.0f, 0.0f, 0.0f));

    characters.resize(2);
    characters[0] = ubo;
    characters[1] = ubo2;

    // characters[1].model = glm::translate(characters[1].model, glm::vec3(4.0f, 0.0f, 0.0f));

//     characters.insert(characters.begin() + characters.size(), ubo);
//     characters.insert(characters.begin() + characters.size(), ubo2);
}
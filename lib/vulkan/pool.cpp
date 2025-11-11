#include <vulkan/init.h>

void VulkanApplication::createDescriptorPool() {
    std::array<VkDescriptorPoolSize, 2> poolSizes{};
    uint32_t texturePoolSize = 1 + textureImages.size();
    std::cout << "descriptor_combined_image_sampler: " << texturePoolSize << std::endl;
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT * 3 + 4);
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT * texturePoolSize + 2);
    // poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    // poolSizes[0].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    // poolSizes[1].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[2].type = VK_DESCRIPTOR_TYPE_SAMPLER;
    // poolSizes[2].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[3].type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
    // poolSizes[3].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[4].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    // poolSizes[4].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[5].type = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
    // poolSizes[5].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[6].type = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
    // poolSizes[6].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[7].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    // poolSizes[7].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[8].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
    // poolSizes[8].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[9].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    // poolSizes[9].descriptorCount = static_cast<uint32_t>(1000);
    // poolSizes[10].type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
    // poolSizes[10].descriptorCount = static_cast<uint32_t>(1000);

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT) * poolSizes.size() + 8;

    if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
    std::cout << "DEBUG CREATE DESCRIPTOR POOL" << std::endl;
}
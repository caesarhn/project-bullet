#include <vulkan/init.h>

void VulkanApplication::createBattleSamplerDescriptorSetLayout(){
    VkDescriptorSetLayoutBinding battleEnemySamplerLayoutBinding{};
    battleEnemySamplerLayoutBinding.binding = 0;
    battleEnemySamplerLayoutBinding.descriptorCount = static_cast<uint32_t>(battleEnemyAssets.size());
    battleEnemySamplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    battleEnemySamplerLayoutBinding.pImmutableSamplers = nullptr;
    battleEnemySamplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    
    VkDescriptorSetLayoutBinding battleEffectSamplerLayoutBinding{};
    battleEffectSamplerLayoutBinding.binding = 1;
    battleEffectSamplerLayoutBinding.descriptorCount = static_cast<uint32_t>(battleEffectAssets.size());
    battleEffectSamplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    battleEffectSamplerLayoutBinding.pImmutableSamplers = nullptr;
    battleEffectSamplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    
    std::array<VkDescriptorSetLayoutBinding, 2> bindings{battleEnemySamplerLayoutBinding, battleEffectSamplerLayoutBinding};
    
    VkDescriptorSetLayoutCreateInfo battleLayoutInfo{};
    battleLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    battleLayoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    battleLayoutInfo.pBindings = bindings.data();
    
    if (vkCreateDescriptorSetLayout(device, &battleLayoutInfo, nullptr, &descriptorSetLayoutBattleSampler) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
    DEBUG_LOG("Create Battle DescriptorSetLayout");
}
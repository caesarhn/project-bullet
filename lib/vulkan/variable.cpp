#include <vulkan/init.h>

std::chrono::time_point<std::chrono::high_resolution_clock> VulkanApplication::lastFrameTime;

void VulkanApplication::initVariables(){
    lastFrameTime = std::chrono::high_resolution_clock::now();
    
    animationMovement = 0; //0=idle, 1=walk
    
    animationToggle = 0;
    updateModel = 0;
    // updateModelValue = {0.0f, 0.0f, 0.0f};
    
    textureAsset = {
        "src/char/char1_idle1.png",
        "src/char/char1_idle2.png",
        "src/char/char1_idle3.png",
        "src/char/char1_idle4.png",
        "src/char/char1_idle5.png"
    };

    vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
    };
}



// struct VulkanApplication::QueueFamilyIndices {
//     std::optional<uint32_t> graphicsFamily;
//     std::optional<uint32_t> presentFamily;

//     bool isComplete() {
//         return graphicsFamily.has_value() && presentFamily.has_value();
//     }
// };

// struct VulkanApplication::SwapChainSupportDetails {
//     VkSurfaceCapabilitiesKHR capabilities;
//     std::vector<VkSurfaceFormatKHR> formats;
//     std::vector<VkPresentModeKHR> presentModes;
// };

// struct VulkanApplication::Vertex {
//     glm::vec3 pos;
//     glm::vec3 color;
//     glm::vec2 texCoord;

//     static VkVertexInputBindingDescription getBindingDescription() {
//         VkVertexInputBindingDescription bindingDescription{};
//         bindingDescription.binding = 0;
//         bindingDescription.stride = sizeof(Vertex);
//         bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

//         return bindingDescription;
//     }

//     static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
//         std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

//         attributeDescriptions[0].binding = 0;
//         attributeDescriptions[0].location = 0;
//         attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
//         attributeDescriptions[0].offset = offsetof(Vertex, pos);

//         attributeDescriptions[1].binding = 0;
//         attributeDescriptions[1].location = 1;
//         attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
//         attributeDescriptions[1].offset = offsetof(Vertex, color);

//         attributeDescriptions[2].binding = 0;
//         attributeDescriptions[2].location = 2;
//         attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
//         attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

//         return attributeDescriptions;
//     }
// };

// struct VulkanApplication::UniformBufferObject {
//     alignas(16) glm::mat4 model;
//     alignas(16) glm::mat4 view;
//     alignas(16) glm::mat4 proj;
//     alignas(16) glm::vec2 set_and_binding;
// };

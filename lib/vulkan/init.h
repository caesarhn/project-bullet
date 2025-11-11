#pragma once
#ifdef __ANDROID__
    #define VK_USE_PLATFORM_ANDROID_KHR
    #include <android/native_window.h>
    #include <vulkan/vulkan.h>             // ← HARUS PERTAMA
    #include <vulkan/vulkan_android.h>
#else
    #define GLFW_INCLUDE_VULKAN
    #include <vulkan/vulkan.h>
    #include <GLFW/glfw3.h>
#endif

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>
#include <stdexcept>
#include <thread>

#include <ui.h>

class VulkanApplication
{
private:

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    //constant logic
    const float CHARACTER_IDLE = 1.0f;
    const float CHARACTER_WALK_RIGHT = 2.0f;
    const float CHARACTER_WALK_DOWN = 3.0f;
    const float CHARACTER_WALK_LEFT = 4.0f;
    const float CHARACTER_WALK_UP = 5.0f;
    
    // Batas FPS
    bool androidExitMainLoop = false;
    const int MAX_FPS = 60;
    const double FRAME_TIME = 1.0 / MAX_FPS;
    static std::chrono::high_resolution_clock::time_point lastFrameTime;
    const int MAX_FRAMES_IN_FLIGHT = 2;
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    const std::vector<const char*> deviceExtensions = {
        "VK_KHR_swapchain"//"VK_KHR_SWAPCHAIN_EXTENSION_NAME"
    };
    
    #ifdef NDEBUG
    const bool enableValidationLayers = false;
    #else
    const bool enableValidationLayers = true;
    #endif
    
    // Animation
    const int TEXTURE_IDLE_MAX_IDX = 4;
    const int TEXTURE_IDLE_OFFSET = 0;
    const int TEXTURE_WALK_MAX_IDX = 9;
    const int TEXTURE_WALK_OFFSET = 5;

    int animationMovement; //0=idle, 1=walk
    int animationToggle;
    int updateModel;
    float updateModelValue[3] = {0.0f, 0.0f, 0.0f};

    std::array<std::string, 6> textureAsset;
    std::array<std::string, 3> characterAsset;
    
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
    
        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;
    
        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
            return bindingDescription;
        }
    
        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
    
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);
    
            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);
    
            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);
    
            return attributeDescriptions;
        }
    };

    struct Vertex2 {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;
    
        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
            return bindingDescription;
        }
    
        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
    
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);
    
            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);
    
            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);
    
            return attributeDescriptions;
        }
    };
    
    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
        alignas(16) glm::vec4 set_and_binding;
        alignas(16) glm::vec4 playerState;
        alignas(16) glm::vec4 animationIdx;
    };
    const glm::mat4 defaultModel = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    const std::vector<glm::vec4> sub_texture_map = {
        {0.0f, 0.0f, 0.1f, 0.1f},
        {0.1f, 0.0f, 0.2f, 0.1f}
    };
    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };
    const std::vector<uint16_t> object_1 = {
        0, 1, 2, 2, 3, 0
    };
    
    std::vector<Vertex> vertices;
    std::vector<Vertex> vertices2;
    struct Object{
        std::string id;
        std::vector<Vertex2> vertices;
    };

    std::vector<Object> objectPool;

    #ifdef __ANDROID__
        ANativeWindow* window = nullptr;
    #else
        GLFWwindow* window = nullptr;
    #endif

    //for UI section
    Gui gui;
    bool lockgui = false;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorSetLayout descriptorSetLayout2;
    VkDescriptorSetLayout descriptorSetLayoutCharacter;
    VkDescriptorSetLayout descriptorSetLayoutCharacterSampler;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkCommandPool commandPool;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    //experimental texture image
    std::vector<VkImage> textureImages;
    std::vector<VkDeviceMemory> textureImageMemorys;
    std::vector<VkImageView> textureImageViews;
    std::vector<VkSampler> textureSamplers;

    //character texture
    std::vector<VkImage> characterImages;
    std::vector<VkDeviceMemory> characterImageMemorys;
    std::vector<VkImageView> characterImageViews;
    std::vector<VkSampler> characterSamplers;

    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer vertexBuffer1;
    VkDeviceMemory vertexBufferMemory1;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    //list vertex buffer
    std::vector<VkBuffer> vertexBuffers;
    std::vector<VkDeviceMemory> vertexBufferMemorys;
    std::vector<VkBuffer> indexBuffers;
    std::vector<VkDeviceMemory> indexBufferMemorys;

    std::vector<VkBuffer> vertexBufferPool;
    std::vector<VkDeviceMemory> vertexBufferMemoryPool;
    std::vector<VkBuffer> indexBufferPool;
    std::vector<VkDeviceMemory> indexBufferMemoryPool;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;

    std::vector<VkBuffer> characterUniformBuffers;
    std::vector<VkDeviceMemory> characterUniformBuffersMemory;
    std::vector<void*> characterUniformBuffersMapped;

    VkDescriptorPool descriptorPool;
    VkDescriptorPool imguiDescriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    std::vector<VkDescriptorSet> descriptorSetsCharacter;
    std::vector<VkDescriptorSet> descriptorSetsCharacterSampler;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    uint32_t currentFrame = 0;

    glm::vec4 texture_set_binding = glm::vec4(0, 1, 0, 0);
    UniformBufferObject ubo{};
    UniformBufferObject ubo2{};
    std::vector<UniformBufferObject> characters;

    bool framebufferResized = false;

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

public:
    void initWindow();
    void initVulkan();
    void initVariables();

    void createInstance();
    void setupDebugMessenger();
    #ifdef __ANDROID__
        void createAndroidSurface();
        void setAndroidWindow(ANativeWindow *win);
    #else
        // void createSurface(GLFWwindow* window);
        void createSurface();
    #endif
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createDescriptorSetLayout();
    void createGraphicsPipeline();
    void createCommandPool();
    void createDepthResources();
    void createFramebuffers();
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();

    //Buffer
    void createVertexBuffer(std::vector<Vertex> Vertex, VkBuffer &VBuffer, VkDeviceMemory &VBMemory);
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void initUbo();

    // gui.createImGuiDescriptorPool(device);
    void createDescriptorSets();
    void createCommandBuffers();
    void createSyncObjects();

    //draw
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void updateUniformBuffer(uint32_t currentImage);
    void drawFrame();
    void mainLoop();

    //update data from ui
    void updateUiData();

    //cleanup
    void cleanupSwapChain();
    void cleanup();
    void recreateSwapChain();

    //helper
    #ifdef __ANDROID__
    #else
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    #endif
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();
    static std::vector<char> readFile(const std::string& filename);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    
    //texture
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void createTextureImages(const char *filename);
    void createCharacterTextureImages(const char *filename);
    void createTextureImageViews();
    void createTextureSamplers();
};




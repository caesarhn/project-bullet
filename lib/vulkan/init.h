#pragma once

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

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
#include <random>

#include <constant.h>
#include <ui/ui.h>
#include <levels/level.h>
#include <logic/logic.h>
#include <app/mechanics/mechanics.h>

class VulkanApplication
{
private:

    //controlAnimation (0, 0, 0, 0) for object
    //controlAnimation (1, 0, 0, 0) for character
    //controlAnimation (2, 0, 0, 0) for linemap
    //contrilAnimation (3, 0, 0, 0) for tilemap

    const uint32_t WIDTH = 1280;
    const uint32_t HEIGHT = 720;

    // //constant logic animation
    // const float CHARACTER_IDLE = 0.0f;
    // const float CHARACTER_WALK = 1.0f;

    // //sub animation
    // const float CHARACTER_WALK_DOWN = 0.0f;
    // const float CHARACTER_WALK_LEFT = 1.0f;
    // const float CHARACTER_WALK_RIGHT = 2.0f;
    // const float CHARACTER_WALK_UP = 3.0f;
    
    // Batas FPS
    bool androidExitMainLoop = false;
    const int MAX_FPS = 60;
    const double FRAME_TIME = 1.0 / MAX_FPS;
    static std::chrono::high_resolution_clock::time_point lastFrameTime;
    const int MAX_FRAMES_IN_FLIGHT = 2;

    //Mouse Loc
    double mouseX = 0.0f;
    double mouseY = 0.0f;
    glm::vec2 mouseWorld;

    // //Events
    // const int EVENT_MENU = 0;
    // const int EVENT_WORLD = 1;
    // const int EVENT_BATTLE = 2;
    // const int EVENT_INVENTORY = 3;
    int currentEvent = 1;

    //Map
    int8_t showMapLine = 0;
    glm::vec4 mapLineArea = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f); //top_left -to- bottom_right

    //character
    int indexMainChar = 0;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME //"VK_KHR_swapchain"
    };
    
    #ifdef NDEBUG
    const bool enableValidationLayers = false;
    #else
    const bool enableValidationLayers = true;
    #endif

    #ifdef DEBUG_MANUAL
    #define DEBUG_LOG(x) // Kosong - tidak melakukan apa-apa
    #else
    #define DEBUG_LOG(x) std::cout << "DEBUG: " << x << std::endl
    #endif

    std::array<std::string, 6> textureAssets;
    std::array<std::string, 12> characterAssets;
    std::array<std::string, 1> battleEnemyAssets;
    std::array<std::string, 7> battleEffectAssets;
    
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
    
    struct UniformBufferObject {
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 projection;
    };
    
    struct UniformBufferObjectEntity {
        alignas(16) glm::mat4 model;
        alignas(16) glm::ivec4 controlAnimation; //vec4(state, sub_state, null, animate_frame)
        alignas(16) glm::ivec4 animationDetail; //vec4(total_sub_state, total_frame, null, null)
        alignas(16) glm::ivec4 samplerIndex; //vec4(idle_idx, walk_idx, run_idx, null)
        alignas(16) glm::ivec4 object; //vec4(object_type, null, null, null)
    };

    struct UniformBufferObjectTile {
        alignas(16) glm::vec4 area; // vec4()
    };

    struct CharacterAttribute {
        int entityId;
        bool isRender;
        bool isUpdated;
        float walkSpeed;
        float runSpeed;
        glm::vec2 position;
        glm::vec2 scale;

        //animation
        int state;
        int subState;
        int frame;
        float animationDuration;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
        glm::ivec4 animationDetail[3]; //(idle, walk, run, null)

        //collicions
        glm::vec2 collicionRect; //vec2(width, height)
    };

    struct ToolAttributes {
        std::string name;
        int addr;
    };

    struct TileMap {
        int width;
        int height;
        int entityId;
        std::vector<int> tiles;

        int& at(int x, int y) {
            return tiles[y * width + x];
        }
    };

    struct BattlePushConstant {
        alignas(16) glm::ivec4 animationIdx;
    };

    const glm::mat4 defaultModel = glm::mat4(1.0f);
    const std::vector<glm::vec4> sub_texture_map = {
        {0.0f, 0.0f, 0.1f, 0.1f},
        {0.1f, 0.0f, 0.2f, 0.1f}
    };
    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,

        //battles_enemy_vertex (idx 18, count 6)
        12, 13, 14, 14, 15, 12,
    };
    
    //Vertex
    std::vector<Vertex> vertices;
    std::vector<Vertex> vertices2;
    std::vector<Vertex> tileBlock;

    std::vector<Vertex> tileLines;
    std::vector<uint16_t> tileLineIndexX;
    std::vector<uint16_t> tileLineIndexY; 

    GLFWwindow* window = nullptr;
    
    //game level
    Level gameLevel;

    //for UI section
    Gui gui;
    Mechanics mechanics;
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
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkPipelineLayout pipelineLayoutDebug;
    VkPipeline graphicsPipelineDebug;
    VkPipelineLayout pipelineLayoutBattle;
    VkPipeline graphicsPipelineBattle;
    
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

    //Battle enemy texture
    std::vector<VkImage> battleEnemyImages;
    std::vector<VkDeviceMemory> battleEnemyImageMemorys;
    std::vector<VkImageView> battleEnemyImageViews;
    std::vector<VkSampler> battleEnemySamplers;

    //Battle Effect texture
    std::vector<VkImage> battleEffectImages;
    std::vector<VkDeviceMemory> battleEffectImageMemorys;
    std::vector<VkImageView> battleEffectImageViews;
    std::vector<VkSampler> battleEffectSamplers;
    
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
    
    VkBuffer vertexBufferTileLine;
    VkDeviceMemory vertexBufferMemoryTileLine;
    VkBuffer indexBufferTileLines;
    VkDeviceMemory indexBufferMemoryTileLines;
    
    //uniform
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    
    std::vector<VkBuffer> entityUniformBuffers;
    std::vector<VkDeviceMemory> entityUniformBuffersMemory;
    std::vector<void*> entityUniformBuffersMapped;

    std::vector<VkBuffer> objectUniformBuffers;
    std::vector<VkDeviceMemory> objectUniformBuffersMemory;
    std::vector<void*> objectUniformBuffersMapped;
    
    VkDescriptorPool descriptorPool;
    VkDescriptorPool imguiDescriptorPool;

    //storage buffer
    std::vector<VkBuffer> tileMapStorageBuffers;
    std::vector<VkDeviceMemory> tileMapStorageBuffersMemory;
    std::vector<void*> tileMapStorageBuffersMapped;

    //Descriptor
    std::vector<VkDescriptorSet> descriptorSets;
    std::vector<VkDescriptorSet> descriptorSetsCharacter;
    std::vector<VkDescriptorSet> descriptorSetsCharacterSampler;
    std::vector<VkDescriptorSet> descriptorSetsTileMap;
    std::vector<VkDescriptorSet> descriptorSetsBattleSampler;
    
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorSetLayout descriptorSetLayoutCharacter;
    VkDescriptorSetLayout descriptorSetLayoutCharacterSampler;
    VkDescriptorSetLayout descriptorSetLayoutTileMap;
    VkDescriptorSetLayout descriptorSetLayoutBattleSampler;
    
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    uint32_t currentFrame = 0;

    //Uniform
    UniformBufferObject ubo{};
    UniformBufferObjectEntity uboCharacter{};
    std::vector<UniformBufferObjectEntity> entities;
    std::vector<CharacterAttribute> charactersAttribute;

    //Maps
    std::vector<TileMap> tileMaps;

    //object tools
    std::vector<ToolAttributes> tools;

    //PushConstant
    BattlePushConstant battlePushConstant;

    bool framebufferResized = false;

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

public:
    void initWindow();
    void initVulkan();
    void initVariables();
    void initTileMaps();

    void createInstance();
    void setupDebugMessenger();

    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();

    //descriptor set layout
    void createDescriptorSetLayout();
    void createBattleSamplerDescriptorSetLayout();
    
    //descriptor set
    void createDescriptorSets();

    //pipelines
    void createGraphicsPipeline();
    void createGraphicsPipelineDebug();
    void createGraphicsPipelineBattle();

    void createCommandPool();
    void createDepthResources();
    void createFramebuffers();
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();

    //Buffer
    void createVertexBuffer(std::vector<Vertex> &Vertex, VkBuffer &VBuffer, VkDeviceMemory &VBMemory);
    void createIndexBuffer(std::vector<uint16_t> &Index, VkBuffer &VBuffer, VkDeviceMemory &VBMemory);
    void createStorageBuffers(std::vector<TileMap> &data, std::vector<VkBuffer> &buffer, std::vector<VkDeviceMemory> &bufferMemory, std::vector<void*> &bufferMapped);
    void createIndexBuffers();
    void createUniformBuffers();
    void createDescriptorPool();
    void initUbo();
    void initPushConstant();
    void initCharacters();

    // gui.createImGuiDescriptorPool(device);
    //Descriptor

    void createCommandBuffers();
    void createSyncObjects();

    //Tile Map
    TileMap loadMap(const std::string& filename);
    TileMap createDefaultMap(int w, int h);
    void saveMap(const std::string& filename, const TileMap& map);

    //draw
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void updateUniformBuffer(uint32_t currentFrame);
    void updateStorageBuffer(uint32_t currentFrame);
    void drawFrame();
    void mainLoop();
    void prepareDrawCharacters(int charIdx, uint32_t currentFrame);
    void animateCharacter();
    void initToolsObject();
    void renderTileMap(VkCommandBuffer commandBuffer, uint32_t currentFrame);

    //update data from ui
    void updateUiData();

    //cleanup
    void cleanupSwapChain();
    void cleanup();
    void recreateSwapChain();

    //helper
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
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
    bool fileExists(const std::string& filename);    

    //texture
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void createTextureImages(const char *filename);
    void createCharacterTextureImages(const char *filename);
    void createTexturesImages(std::vector<VkImage> &images, std::vector<VkDeviceMemory> &imagesMemorys, const char *filename);
    void createTextureImageViews();
    void createTexturesImagesViews(std::vector<VkImage> &images, std::vector<VkImageView> &imagesView);

    void createTextureSamplers();
    void createTexturesSamplers(std::vector<VkSampler> &samplers, std::vector<VkImage> &images);

    //physics
    bool checkCollision(glm::vec4 a, glm::vec4 b);
    void charMove(int chardx);

    //event
    void battleEvent();

    //test
    void createVertexBufferHehe();

    //recordCommandBuffer
    void recordCommandBufferBattle(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    //application
    bool isWindowClosed();
    void prepLoop();
    void beginLoop();
    void endLoop();
};




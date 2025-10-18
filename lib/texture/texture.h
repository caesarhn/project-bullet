#include <vulkan/init.h>

class texture{
    
public:
    //experimental texture image
    std::vector<VkImage> textureImages;
    std::vector<VkDeviceMemory> textureImageMemorys;
    std::vector<VkImageView> textureImageViews;
    std::vector<VkSampler> textureSamplers;

    void experimentalCreateTextureImage(const char *filename);
    void experimentalCreateTextureImageView();
    void experimentalCreateTextureSampler();
};

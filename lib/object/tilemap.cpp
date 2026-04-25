#include <vulkan/init.h>

void VulkanApplication::initTileMaps(){
    tileMaps.resize(1);

    if(fileExists("default_map.bin")){
        tileMaps[0] = loadMap("default_map.bin");
    }else{
        tileMaps[0] = createDefaultMap(10,10);
        saveMap("default_map.bin", tileMaps[0]);
    }
}

void VulkanApplication::saveMap(const std::string& filename, const TileMap& map) {
    std::ofstream file(filename, std::ios::binary);

    file.write((char*)&map.width, sizeof(int));
    file.write((char*)&map.height, sizeof(int));

    file.write(
        (char*)map.tiles.data(),
        map.tiles.size() * sizeof(int)
    );

    file.close();
}

VulkanApplication::TileMap VulkanApplication::loadMap(const std::string& filename) {
    TileMap map;

    std::ifstream file(filename, std::ios::binary);

    file.read((char*)&map.width, sizeof(int));
    file.read((char*)&map.height, sizeof(int));

    map.tiles.resize(map.width * map.height);

    file.read(
        (char*)map.tiles.data(),
        map.tiles.size() * sizeof(int)
    );

    std::cout << "Width: " << map.width << std::endl;
    std::cout << "Height: " << map.height << std::endl;
    std::cout << "Height: " << map.tiles.size() << std::endl;

    file.close();

    return map;
}

VulkanApplication::TileMap VulkanApplication::createDefaultMap(int w, int h) {
    TileMap map;
    map.width = w;
    map.height = h;
    map.tiles.resize(w * h);

    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            map.at(x,y) = 6; // default tile
        }
    }

    return map;
}

void VulkanApplication::renderTileMap(VkCommandBuffer commandBuffer, uint32_t currentFrame){
    VkDeviceSize offsets[] = {0};

    vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer1, offsets);
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
    
    memcpy(entityUniformBuffersMapped[(6 * MAX_FRAMES_IN_FLIGHT)+currentFrame], &entities[6], sizeof(uboCharacter));
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &descriptorSetsCharacter[(6*MAX_FRAMES_IN_FLIGHT)+currentFrame], 0, nullptr);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 3, 1, &descriptorSetsTileMap[currentFrame], 0, nullptr);
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(6), 1, 12, 0, 0);
}

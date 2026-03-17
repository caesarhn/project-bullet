#include <vulkan/init.h>

void VulkanApplication::initTileMaps(){
    tileMaps.resize(10);

    if(fileExists("default_map.bin")){
        tileMaps[0] = loadMap("default_map.bin")
    }else{
        tileMaps[0] = createDefaultMap(100,100);
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

TileMap VulkanApplication::loadMap(const std::string& filename) {
    TileMap map;

    std::ifstream file(filename, std::ios::binary);

    file.read((char*)&map.width, sizeof(int));
    file.read((char*)&map.height, sizeof(int));

    map.tiles.resize(map.width * map.height);

    file.read(
        (char*)map.tiles.data(),
        map.tiles.size() * sizeof(int)
    );

    file.close();

    return map;
}

TileMap VulkanApplication::createDefaultMap(int w, int h) {
    TileMap map;
    map.width = w;
    map.height = h;
    map.tiles.resize(w * h);

    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            map.at(x,y) = 0; // default tile
        }
    }

    return map;
}

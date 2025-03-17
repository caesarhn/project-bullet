#include <iostream>
#include <fstream>

int main() {
    std::string filename = "shaders/vert.spv";

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "❌ Error: Gagal membuka file " << filename << std::endl;
        return 1;
    }

    std::cout << "✅ File berhasil dibuka!" << std::endl;
    return 0;
}

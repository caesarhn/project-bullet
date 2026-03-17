#include <vulkan/init.h>

void VulkanApplication::initToolsObject(){
    entities[4].model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    entities[4].animationDetail = glm::ivec4(4, 8, 0, 0);
    entities[4].controlAnimation = glm::ivec4(0, 0, 0, 0);
    entities[4].samplerIndex = glm::ivec4(0, 1, 2, 0);
    entities[4].object = glm::ivec4(2, 0, 0, 0);
}
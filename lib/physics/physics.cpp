#include <vulkan/init.h>

bool VulkanApplication::checkCollision(glm::vec4 a, glm::vec4 b){
    return (a.x < b.x + b.z &&
            a.x + a.z > b.x &&
            a.y < b.y + b.w &&
            a.y + a.w > b.y);
}
#include <app/app.h>

Application::Application(){
    std::cout<<"app is running..."<<std::endl;
    Vulkan = new VulkanApplication;
    Vulkan->initWindow();
    Vulkan->initVulkan();
    Vulkan->initUbo();
    Vulkan->mainLoop();
    Vulkan->cleanup();
}
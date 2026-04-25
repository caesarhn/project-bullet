// #pragma once

#include <app/app.h>
#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <app/gameConstant.h>

Application::Application(){
    std::cout<<"app is running..."<<std::endl;
    Vulkan = new VulkanApplication;
    Vulkan->initWindow();
    Vulkan->initVulkan();
    std::cout<<"APP DEBUG"<<std::endl;
    Vulkan->mainLoop();
    Vulkan->cleanup();
}

void Application::mainLoop(){
    while (Vulkan->isWindowClosed()){
        
    }  
}
#include <vulkan/init.h>
#include <logic/logic.h>

void VulkanApplication::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChainExtent;

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {{0.3f, 0.3f, 0.3f, 1.0f}};
    clearValues[1].depthStencil = {1.0f, 0};

    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) swapChainExtent.width;
        viewport.height = (float) swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = swapChainExtent;
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
        
        VkBuffer vertexBuffers[] = {vertexBuffer};
        VkBuffer vertexBuffers1[] = {vertexBuffer1};
        VkBuffer vertexBufferTiles[] = {vertexBufferTile};
        VkDeviceSize offsets[] = {0};
        // vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
        
        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[currentFrame], 0, nullptr);
        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &descriptorSets[currentFrame + 2], 0, nullptr);
        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 3, 1, &descriptorSetsCharacterSampler[currentFrame], 0, nullptr);
        // std::cout << "DEBUG Record Command Buffer " << swapChainExtent.width <<std::endl;
        // vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

        // vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 2, 1, &descriptorSetsCharacter[currentFrame+2], 0, nullptr);
        // vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
        
        // vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 2, 1, &descriptorSetsCharacter[currentFrame+4], 0, nullptr);
        // vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
        
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers1, offsets);
        vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
        for(int i = 0; i < characters.size(); i++){
            if(charactersAttribute[i].isRender == true){
                // std::cout << "debug drawing: " << characters[i].controlAnimation[0] << " " << characters[i].controlAnimation[1] << std::endl;
                vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 2, 1, &descriptorSetsCharacter[currentFrame+(2*i)], 0, nullptr);
                vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
            }
        }

        std::cout << 
        ubo.view[0][0] << "  " << ubo.view[1][0] << "  " << ubo.view[2][0] << "  " << ubo.view[3][0] << std::endl <<
        ubo.view[0][1] << "  " << ubo.view[1][1] << "  " << ubo.view[2][1] << "  " << ubo.view[3][1] << std::endl <<
        ubo.view[0][2] << "  " << ubo.view[1][2] << "  " << ubo.view[2][2] << "  " << ubo.view[3][2] << std::endl <<
        ubo.view[0][3] << "  " << ubo.view[1][3] << "  " << ubo.view[2][3] << "  " << ubo.view[3][3] << std::endl <<
        std::endl;

        std::cout << 
        ubo.projection[0][0] << "  " << ubo.projection[1][0] << "  " << ubo.projection[2][0] << "  " << ubo.projection[3][0] << std::endl <<
        ubo.projection[0][1] << "  " << ubo.projection[1][1] << "  " << ubo.projection[2][1] << "  " << ubo.projection[3][1] << std::endl <<
        ubo.projection[0][2] << "  " << ubo.projection[1][2] << "  " << ubo.projection[2][2] << "  " << ubo.projection[3][2] << std::endl <<
        ubo.projection[0][3] << "  " << ubo.projection[1][3] << "  " << ubo.projection[2][3] << "  " << ubo.projection[3][3] << std::endl <<

        std::endl;

        for(int i =0; i < 3; i++){
            std::cout << "ANJAAAIII " << i << std::endl;
            std::cout << " " << charactersAttribute[i].isRender << " " << charactersAttribute[i].position.x << std::endl;

            std::cout << "animation detail: " << 
                characters[i].animationDetail.x << " " <<
                characters[i].animationDetail.y << " " <<
                " animation control: " <<
                characters[i].controlAnimation[0] << " " <<
                characters[i].controlAnimation[1] << " " <<
                characters[i].controlAnimation[2] << " " <<
                characters[i].controlAnimation[3] << "      " <<
                characters[i].model[3][0] << " " <<
                characters[i].model[3][1] << " " <<
                characters[i].model[3][2] << " "
            << std::endl;
        }


        std::cout << " " << sizeof(UniformBufferObject) << " " << sizeof(UniformBufferObjectCharacter)<< std::endl;
        std::cout << " " << sizeof(uniformBuffers[0]) << " " << sizeof(characterUniformBuffers[0])<< std::endl;
        std::cout << " " << sizeof(uniformBuffersMemory[0]) << " " << sizeof(characterUniformBuffersMemory[0])<< std::endl;
        std::cout << " " << sizeof(uniformBuffersMapped) << " " << sizeof(characterUniformBuffersMapped)<< std::endl;

        glm::mat4 result = ubo.projection * ubo.view * defaultModel;
        glm::vec4 nana = result * glm::vec4(-2.0f, 3.0f, 0.0f, 1.0f);
        std::cout << 
        result[0][0] << "  " << result[1][0] << "  " << result[2][0] << "  " << result[3][0] << std::endl <<
        result[0][1] << "  " << result[1][1] << "  " << result[2][1] << "  " << result[3][1] << std::endl <<
        result[0][2] << "  " << result[1][2] << "  " << result[2][2] << "  " << result[3][2] << std::endl <<
        result[0][3] << "  " << result[1][3] << "  " << result[2][3] << "  " << result[3][3] << std::endl;

        std::cout << "output" << glm::to_string(nana);


        #ifdef __ANDROID__
        #else
        gui.renderUI();
        gui.recordImGuiCommands(commandBuffer);
        #endif
    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void VulkanApplication::updateUniformBuffer(uint32_t currentImage) {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(UniformBufferObject));

        memcpy(characterUniformBuffersMapped[currentImage], &characters[0], sizeof(UniformBufferObjectCharacter));
        memcpy(characterUniformBuffersMapped[currentImage+2], &characters[1], sizeof(UniformBufferObjectCharacter));
        memcpy(characterUniformBuffersMapped[currentImage+4], &characters[2], sizeof(UniformBufferObjectCharacter));
        for(int i = 3; i < characters.size(); i++){
            memcpy(characterUniformBuffersMapped[currentImage+(i*2)], &characters[i], sizeof(UniformBufferObjectCharacter));
        }
        std::cout << "Current frame: " << currentImage << " "<< std::endl;
    }

void VulkanApplication::drawFrame() {
    vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        recreateSwapChain();
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    updateUniformBuffer(currentFrame);

    vkResetFences(device, 1, &inFlightFences[currentFrame]);

    vkResetCommandBuffer(commandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
    recordCommandBuffer(commandBuffers[currentFrame], imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
        framebufferResized = false;
        recreateSwapChain();
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanApplication::mainLoop() {
    // #ifdef __ANDROID__
    // int frame = 0;
    // float animationFrame = 1.0f;
    // auto lastFrameTime = std::chrono::high_resolution_clock::now();
    
    // while (!androidExitMainLoop) {
    //     // Frame timing (sama seperti desktop)
    //     auto currentTime = std::chrono::high_resolution_clock::now();
    //     double elapsedTime = std::chrono::duration<double>(currentTime - lastFrameTime).count();
        
    //     if (elapsedTime < FRAME_TIME) {
    //         std::this_thread::sleep_for(std::chrono::duration<double>(FRAME_TIME - elapsedTime));
    //     }
        
    //     lastFrameTime = std::chrono::high_resolution_clock::now();
        
    //     // Process Android events (menggantikan glfwPollEvents)
    //     // processAndroidEvents();
        
    //     // Animation logic (SAMA PERSIS dengan desktop)
    //     // if(frame == 12){
    //         //     ubo.animationIdx = animationFrame;
            
    //         //     if(animationFrame == 8){
    //     //         animationFrame = 1;
    //     //     } else {
    //         //         animationFrame++;
    //         //     }
    //     // }

    //     // Execute World Logic (SAMA PERSIS dengan desktop)
    //     if(animationMovement == 1 && frame == 12){
    //         texture_set_binding[0] = 1;
    //         if(texture_set_binding[1] < TEXTURE_WALK_OFFSET || texture_set_binding[1] > TEXTURE_WALK_MAX_IDX){
    //             texture_set_binding[1] = TEXTURE_WALK_OFFSET - 1;
    //         }
    //         texture_set_binding[1] = texture_set_binding[1] + 1;
    //         // LOGI("texture bind : %d %d", texture_set_binding[0], texture_set_binding[1]);
    //         frame = 0;
    //     }
    //     else if(animationMovement == 0 && frame == 10){
    //         texture_set_binding[1] = texture_set_binding[1] + 1;
    //         texture_set_binding[0] = 1;
    //         // LOGI("texture bind : %d %d", texture_set_binding[0], texture_set_binding[1]);
    //         if(texture_set_binding[1] >= textureAsset.size()){
    //             texture_set_binding[1] = 0;
    //         }
    //         frame = 0;
    //     }
        
    //     frame++;
    //     if(frame == 60){
    //         frame = 0;
    //     }
    //     updateUiData();
    //     drawFrame();
    // }
    
    // vkDeviceWaitIdle(device);
    // #else
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    int frame = 0;
    int animationFrame = 0;
    int walk_frame = 0;
    int animationWalk = 0;
    int idleDirection = 0;

    //random
    std::random_device rd;                 // sumber random
    std::mt19937 gen(rd());                // generator Mersenne Twister
    std::uniform_int_distribution<> dist(0, 4);
    std::uniform_int_distribution<> walks(0, 10);
    std::uniform_int_distribution<> xy(0, 1);
    float into = 0.0f;
    int x_or_y = xy(gen);
    int x = dist(gen);
    glm::vec3 translateRandom = glm::vec3(0.0f, 0.0f, 0.0f);
    int randomContainer;

    //world
    WorldLevel world;

    Walk walked_down{9};
    Walk walked_up{9};
    Walk walked_right{9};
    Walk walked_left{9};

    Walk idle{7};

    charactersAttribute[0].isRender = true;
    charactersAttribute[1].isRender = true;
    charactersAttribute[2].isRender = true;

    while (!glfwWindowShouldClose(window)) {
        float xx = 2.0f;
        // std::cout << "PLAYER STATE: " << characters[1].playerState[0] << " " << characters[1].playerState[1] << std::endl;
        // limit framerate
        auto currentTime = std::chrono::high_resolution_clock::now();
        double elapsedTime = std::chrono::duration<double>(currentTime - lastFrameTime).count();
        
        if (elapsedTime < FRAME_TIME) {
            std::this_thread::sleep_for(std::chrono::duration<double>(FRAME_TIME - elapsedTime));
        }
        
        lastFrameTime = std::chrono::high_resolution_clock::now();
        glfwPollEvents();
        // processInput();
        // std::cout << frame << " LOCKGUI " << lockgui << std::endl;

        if(lockgui == false){
            if(characters[1].controlAnimation[1] == 0.0f){
                charactersAttribute[1].idle.animate(&characters[1].controlAnimation[3]);
            }
            else if(characters[1].controlAnimation[1] == 1.0f){
                charactersAttribute[1].walk.animate(&characters[1].controlAnimation[3]);
            }
        }else{
            characters[1].animationDetail = glm::vec4(4.0f, 10.0f, 0.0f, 0.0f);
            characters[1].controlAnimation[0] = 1.0f;
            if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
                characters[1].controlAnimation[1] = CHARACTER_WALK_DOWN;
                charactersAttribute[1].walk.animate(&characters[1].controlAnimation[3]);
                characters[1].model = glm::translate(characters[1].model, glm::vec3(0.0f, 0.05f, 0.0f));
                idleDirection = 0;
            }
            if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
                characters[1].controlAnimation[1] = CHARACTER_WALK_LEFT;
                charactersAttribute[1].walk.animate(&characters[1].controlAnimation[3]);
                characters[1].model = glm::translate(characters[1].model, glm::vec3(0.05f, 0.0f, 0.0f));
                idleDirection = 1;
            }
            else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
                characters[1].controlAnimation[1] = CHARACTER_WALK_RIGHT;
                charactersAttribute[1].walk.animate(&characters[1].controlAnimation[3]);
                characters[1].model = glm::translate(characters[1].model, glm::vec3(-0.05f, 0.0f, 0.0f));
                idleDirection = 2;
            }
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
                // std::cout << "WWWWWW" << std::endl;
                characters[1].controlAnimation[1] = CHARACTER_WALK_UP;
                charactersAttribute[1].walk.animate(&characters[1].controlAnimation[3]);
                characters[1].model = glm::translate(characters[1].model, glm::vec3(0.0f, -0.05f, 0.0f));
                idleDirection = 3;
            }
            if(
                glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS &&
                glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS &&
                glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS &&
                glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS
            ){
                characters[1].animationDetail = glm::vec4(4.0f, 8.0f, 0.0f, 0.0f);
                std::cout << "IDLE" << std::endl;
                characters[1].controlAnimation[0] = CHARACTER_IDLE;
                characters[1].controlAnimation[1] = (float)(idleDirection);
                charactersAttribute[1].idle.animate(&characters[1].controlAnimation[3]);
            }
        }

        //non player
        for(int i = 3; i < 20; i++){
            characters[i].animationDetail = glm::vec4(4.0f, 10.0f, 0.0f, 0.0f);
            randomContainer = dist(gen);
            characters[i].controlAnimation[0] = CHARACTER_WALK;
            if(randomContainer == 0){
                translateRandom.y = -0.05f;
            }
            else if(randomContainer == 1){
                translateRandom.x = -0.05f;
            }
            else if(randomContainer == 2){
                translateRandom.x = 0.05f;
            }
            else if(randomContainer == 4){
                translateRandom.y = 0.05f;
            }
            charactersAttribute[i].direction = randomContainer;
            characters[i].model = glm::translate(defaultModel, translateRandom);

            characters[i].controlAnimation[1] = (float)(charactersAttribute[i].direction);
            charactersAttribute[i].walk.animate(&characters[i].controlAnimation[3]);

            translateRandom.x = 0.0f;
            translateRandom.y = 0.0f;
        }

        characters[0].animationDetail = glm::vec4(4.0f, 8.0f, 0.0f, 0.0f);
        characters[0].controlAnimation[0] = CHARACTER_IDLE;
        characters[0].controlAnimation[1] = (float)(idleDirection);
        characters[0].model = glm::translate(defaultModel, glm::vec3(0.0f, 0.0001f, 0.0f));
        charactersAttribute[0].idle.animate(&characters[0].controlAnimation[3]);

        characters[2].animationDetail = glm::vec4(4.0f, 8.0f, 0.0f, 0.0f);
        characters[2].controlAnimation[0] = CHARACTER_IDLE;
        characters[2].controlAnimation[1] = (float)(idleDirection);
        characters[2].model = glm::translate(defaultModel, glm::vec3(0.0f, 0.0001f, 0.0f));
        charactersAttribute[2].idle.animate(&characters[2].controlAnimation[3]);

        frame++;
        if(frame == 60){
            frame = 0;
        }
        updateUiData();
        drawFrame();
    }
    vkDeviceWaitIdle(device);
    // #endif
    std::cout << "MAIN LOOP DEBUG" << std::endl;
}
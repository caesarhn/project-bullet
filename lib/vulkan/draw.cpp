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
        VkBuffer vertexBufferTiles[] = {vertexBufferTileLine};
        VkDeviceSize offsets[] = {0};
    
    
        DEBUG_LOG("RECORD COMMAND BUFFER");
    
        if(currentEvent == EVENT_WORLD){
            vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

            vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers1, offsets);
            vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
    
            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[currentFrame], 0, nullptr);
            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &descriptorSetsCharacter[currentFrame], 0, nullptr);
            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 2, 1, &descriptorSetsCharacterSampler[currentFrame], 0, nullptr);
            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 3, 1, &descriptorSetsTileMap[currentFrame], 0, nullptr);
            
            for(int i = 0; i < charactersAttribute.size(); i++){
                if(charactersAttribute[i].isRender == true){
                    // prepareDrawCharacters(i, currentFrame);
                    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &descriptorSetsCharacter[(i*MAX_FRAMES_IN_FLIGHT)+currentFrame], 0, nullptr);
    
                    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(6), 1, 0, 0, 0);
    
                }
            }
    
            renderTileMap(commandBuffer, currentFrame);

            if(gui.showTile){
                // vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBufferTiles, offsets);
                // vkCmdBindIndexBuffer(commandBuffer, indexBufferTileLines, 0, VK_INDEX_TYPE_UINT16);
                // memcpy(entityUniformBuffersMapped[(4 * MAX_FRAMES_IN_FLIGHT)+currentFrame], &entities[4], sizeof(uboCharacter));
                // // prepareDrawCharacters(2, currentFrame);
                // vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &descriptorSetsCharacter[(4*MAX_FRAMES_IN_FLIGHT)+currentFrame], 0, nullptr);
                // vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(tileLineIndexX.size()), 1, 0, 0, 0);
            }
            if(gui.debugCol){
                vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelineDebug);
                vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
                vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
                vkCmdSetLineWidth(commandBuffer, 1.0f);
    
                vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayoutDebug, 0, 1, &descriptorSets[currentFrame], 0, nullptr);
                vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayoutDebug, 1, 1, &descriptorSetsCharacter[currentFrame], 0, nullptr);
    
                vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers1, offsets);
                vkCmdDraw(commandBuffer, 3, 1, 0, 0);
            }
        }
        else if(currentEvent == EVENT_BATTLE){
            vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelineBattle);
            DEBUG_LOG(battleEnemyImages.size());
            vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
            vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
            
            DEBUG_LOG("EVENT BATTLE");
            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayoutBattle, 0, 1, &descriptorSetsBattleSampler[currentFrame], 0, nullptr);
            vkCmdPushConstants(commandBuffer, pipelineLayoutBattle, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(BattlePushConstant), &battlePushConstant);

            vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers1, offsets);
            vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);

            vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(6), 1, 18, 0, 0);
            // vkCmdDraw(commandBuffer, 3, 1, 0, 0);
        }


        gui.renderUI((float) swapChainExtent.width, (float) swapChainExtent.height);
        gui.recordImGuiCommands(commandBuffer);


    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void VulkanApplication::updateUniformBuffer(uint32_t currentFrame) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    uboCharacter.model = glm::mat4(1.0f);

    memcpy(uniformBuffersMapped[currentFrame], &ubo, sizeof(ubo));
    DEBUG_LOG("updated uniform buffer");
    memcpy(entityUniformBuffersMapped[(3*MAX_FRAMES_IN_FLIGHT) + currentFrame], &entities[3], sizeof(uboCharacter));

    if(showMapLine == 1){

    }

}

void VulkanApplication::updateStorageBuffer(uint32_t currentFrame){
    for(int i = 0; i < tileMaps.size(); i++){
        memcpy(tileMapStorageBuffersMapped[(i * MAX_FRAMES_IN_FLIGHT) + currentFrame], tileMaps[i].tiles.data(), tileMaps[i].tiles.size() * sizeof(int));
    }
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

    for(int i = 0; i < charactersAttribute.size(); i++){
        if(charactersAttribute[i].isRender == true){
            prepareDrawCharacters(i, currentFrame);
        }
    }

    updateUniformBuffer(currentFrame);
    updateStorageBuffer(currentFrame);
    // updateStorageBuffer(currentFrame);

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

    for(int x = 0; x < 100; x++){
        std::cout << x <<" "<< tileMaps[0].tiles[x] << std::endl; 
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // break;

        //mouse logic
        glfwGetCursorPos(window, &mouseX, &mouseY);
        float ndcX = (2.0f * mouseX / swapChainExtent.width) - 1.0f;
        float ndcY = 1.0f - (2.0f * mouseY / swapChainExtent.height);
        glm::mat4 invVP = glm::inverse(ubo.projection * ubo.view);

        glm::vec4 worldPos = invVP * glm::vec4(ndcX, ndcY, 0.0f, 1.0f);
        worldPos /= worldPos.w;

        mouseWorld = glm::vec2(worldPos.x, worldPos.y);

        //moving character
        charMove(indexMainChar);

        // break;
        float xx = 2.0f;
        // std::cout << "PLAYER STATE: " << characters[1].playerState[0] << " " << characters[1].playerState[1] << std::endl;
        
        // limit framerate
        auto currentTime = std::chrono::high_resolution_clock::now();
        double elapsedTime = std::chrono::duration<double>(currentTime - lastFrameTime).count();
        
        if (elapsedTime < FRAME_TIME) {
            std::this_thread::sleep_for(std::chrono::duration<double>(FRAME_TIME - elapsedTime));
        }
        charactersAttribute[indexMainChar].isUpdated = true;
        animateCharacter();
        
        lastFrameTime = std::chrono::high_resolution_clock::now();

        //render
        std::cout << "MAIN LOOP DEBUG" << std::endl;
        updateUiData();
        drawFrame();
    }
    vkDeviceWaitIdle(device);
    // #endif
}
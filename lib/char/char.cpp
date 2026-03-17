#include <vulkan/init.h>

void VulkanApplication::initCharacters(){
    entities.resize(6);
    charactersAttribute.resize(4);

    //char1
    entities[0].model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    entities[0].animationDetail = glm::ivec4(4, 8, 0, 0);
    entities[0].controlAnimation = glm::ivec4(0, 0, 0, 0);
    entities[0].samplerIndex = glm::ivec4(0, 1, 2, 0);
    entities[0].object = glm::ivec4(1, 0, 0, 0);

    charactersAttribute[0].entityId = 0;
    charactersAttribute[0].isRender = true;
    charactersAttribute[0].isUpdated = true;
    charactersAttribute[0].walkSpeed = 0.01f;
    charactersAttribute[0].runSpeed = 0.05f;
    charactersAttribute[0].position = glm::vec2(0.0f, 0.0f);
    charactersAttribute[0].collicionRect = glm::vec2(0.5f, 1.0f);

    charactersAttribute[0].state = 0;
    charactersAttribute[0].subState = 0;
    charactersAttribute[0].animationDetail[0] = glm::ivec4(4, 8, 0, 0);
    charactersAttribute[0].animationDetail[1] = glm::ivec4(4, 10, 0, 0);
    charactersAttribute[0].animationDetail[2] = glm::ivec4(4, 8, 0, 0);
    charactersAttribute[0].frame = 0;
    charactersAttribute[0].animationDuration = 1.0f;

    //char2
    entities[1].model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    entities[1].animationDetail = glm::ivec4(2, 5, 0, 0);
    entities[1].controlAnimation = glm::ivec4(0, 0, 0, 0);
    entities[1].samplerIndex = glm::ivec4(3, 1, 2, 0);
    entities[1].object = glm::ivec4(1, 0, 0, 0);

    charactersAttribute[1].entityId = 1;
    charactersAttribute[1].isRender = true;
    charactersAttribute[1].isUpdated = true;
    charactersAttribute[1].walkSpeed = 0.01f;
    charactersAttribute[1].runSpeed = 0.05f;
    charactersAttribute[1].position = glm::vec2(2.0f, 2.0f);
    charactersAttribute[1].collicionRect = glm::vec2(1.0f, 2.0f);

    charactersAttribute[1].state = 0;
    charactersAttribute[1].subState = 0;
    charactersAttribute[1].animationDetail[0] = glm::ivec4(1, 5, 0, 0);
    charactersAttribute[1].animationDetail[1] = glm::ivec4(4, 10, 0, 0);
    charactersAttribute[1].animationDetail[2] = glm::ivec4(4, 8, 0, 0);
    charactersAttribute[1].frame = 0;
    charactersAttribute[1].animationDuration = 1.0f;

    //char3
    entities[2].model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    entities[2].animationDetail = glm::ivec4(1, 10, 0, 0);
    entities[2].controlAnimation = glm::ivec4(0, 0, 0, 0);
    entities[2].samplerIndex = glm::ivec4(4, 1, 2, 0);
    entities[2].object = glm::ivec4(1, 0, 0, 0);

    charactersAttribute[2].entityId = 2;
    charactersAttribute[2].isRender = true;
    charactersAttribute[2].isUpdated = true;
    charactersAttribute[2].walkSpeed = 0.01f;
    charactersAttribute[2].runSpeed = 0.05f;
    charactersAttribute[2].position = glm::vec2(-2.0f, -2.0f);
    charactersAttribute[2].collicionRect = glm::vec2(0.5f, 1.0f);

    charactersAttribute[2].state = 0;
    charactersAttribute[2].subState = 0;
    charactersAttribute[2].animationDetail[0] = glm::ivec4(1, 10, 0, 0);
    charactersAttribute[2].animationDetail[1] = glm::ivec4(4, 10, 0, 0);
    charactersAttribute[2].animationDetail[2] = glm::ivec4(4, 8, 0, 0);
    charactersAttribute[2].frame = 0;
    charactersAttribute[2].animationDuration = 1.0f;

    //char4
    entities[3].model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    entities[3].animationDetail = glm::ivec4(4, 8, 0, 0);
    entities[3].controlAnimation = glm::ivec4(0, 0, 0, 0);
    entities[3].samplerIndex = glm::ivec4(0, 1, 2, 0);
    entities[3].object = glm::ivec4(1, 0, 0, 0);

    charactersAttribute[3].entityId = 3;
    charactersAttribute[3].isRender = true;
    charactersAttribute[3].isUpdated = true;
    charactersAttribute[3].walkSpeed = 0.01f;
    charactersAttribute[3].runSpeed = 0.05f;
    charactersAttribute[3].position = glm::vec2(-5.0f, -5.0f);
    charactersAttribute[3].collicionRect = glm::vec2(0.5f, 1.0f);

    charactersAttribute[3].state = 0;
    charactersAttribute[3].subState = 0;
    charactersAttribute[3].animationDetail[0] = glm::ivec4(4, 8, 0, 0);
    charactersAttribute[3].animationDetail[1] = glm::ivec4(4, 10, 0, 0);
    charactersAttribute[3].animationDetail[2] = glm::ivec4(4, 8, 0, 0);
    charactersAttribute[3].frame = 0;
    charactersAttribute[3].animationDuration = 1.0f;

    initToolsObject();



}

void VulkanApplication::prepareDrawCharacters(int charIdx, u_int32_t currentFrame){
    CharacterAttribute currentCharAttr = charactersAttribute[charIdx];

    if(charactersAttribute[charIdx].isUpdated == true){
        entities[charIdx].model = glm::translate(glm::mat4(1.0f), glm::vec3(currentCharAttr.position, 0.0f));
        entities[charIdx].animationDetail = currentCharAttr.animationDetail[currentCharAttr.state];
        entities[charIdx].controlAnimation = glm::ivec4(currentCharAttr.state, currentCharAttr.subState, 0, currentCharAttr.frame);
    }
    charactersAttribute[charIdx].isUpdated == false;
    memcpy(entityUniformBuffersMapped[(charIdx * MAX_FRAMES_IN_FLIGHT)+currentFrame], &entities[charIdx], sizeof(uboCharacter));
}

void VulkanApplication::animateCharacter(){
    for(int i = 0; i < entities.size(); i++){
        if(charactersAttribute[i].isUpdated == true){
            CharacterAttribute currentChar = charactersAttribute[i];
            auto currentTime = std::chrono::high_resolution_clock::now();
            double charFrameTime = currentChar.animationDuration / double(currentChar.animationDetail[currentChar.state].y);
            if(std::chrono::duration<double>(currentTime - currentChar.lastFrameTime).count() > charFrameTime){
                // std::cout << charFrameTime << "  --  " << std::chrono::duration<double>(currentTime - currentChar.lastFrameTime).count() << std::endl;
                if(charactersAttribute[i].frame < entities[i].animationDetail.y - 1){
                    charactersAttribute[i].frame += 1;
                }else{
                    charactersAttribute[i].frame = 0;
                }
                charactersAttribute[i].lastFrameTime = std::chrono::high_resolution_clock::now();
            }
        }
    }
}

void checkCollisionChar (){
    
}

void VulkanApplication::charMove(int charIdx){
    CharacterAttribute currentChar = charactersAttribute[charIdx];

    bool w = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    bool a = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    bool s = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    bool d = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

    glm::vec2 moveTo(0.0f, 0.0f);
    if(w){
        moveTo.y -= currentChar.walkSpeed;
    }
    if(s){
        moveTo.y += currentChar.walkSpeed;
    }
    if(a){
        moveTo.x += currentChar.walkSpeed;
    }
    if(d){
        moveTo.x -= currentChar.walkSpeed;
    }

    if(!(moveTo.x == 0 && moveTo.y == 0)){

        glm::vec2 newPosition(currentChar.position.x + moveTo.x, currentChar.position.y + moveTo.y);
        bool collision = false;
        for(int i = 0; i < entities.size(); i++){
            if(i != charIdx){
                collision = checkCollision(glm::vec4(newPosition, currentChar.collicionRect),
                                            glm::vec4(charactersAttribute[i].position, charactersAttribute[i].collicionRect));
                if(collision == true){
                    break;
                }
            }
        }

        if(!collision){
            currentChar.position = newPosition;
            currentChar.state = 1;
        }
    
        if(moveTo.x > 0){
            currentChar.subState = 2;
        }
        else if(moveTo.x < 0){
            currentChar.subState = 1;
        }
    
        if(moveTo.y > 0){
            currentChar.subState = 0;
        }
        else if(moveTo.y < 0){
            currentChar.subState = 3;
        }

    }else{
        currentChar.state = 0;
    }

    charactersAttribute[charIdx] = currentChar;
}
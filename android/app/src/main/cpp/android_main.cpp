#include <android_native_app_glue.h>
#include <android/log.h>
#include <android/native_window.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>

#include <vulkan/init.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "VulkanApp", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "VulkanApp", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "VulkanApp", __VA_ARGS__))

// Global Vulkan application instance
static VulkanApplication* g_VulkanApp = nullptr;

// Handle command events from Android
static void handle_cmd(android_app* app, int32_t cmd) {
    VulkanApplication* vulkanApp = (VulkanApplication*)app->userData;
    
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            LOGI("APP_CMD_INIT_WINDOW - Initializing Vulkan");
            if (app->window != nullptr && vulkanApp != nullptr) {
                // Set the Android window and initialize Vulkan
                #ifdef __ANDROID__
                vulkanApp->setAndroidWindow(app->window);
                #endif
                try {
                    vulkanApp->initWindow();
                    vulkanApp->initVulkan();
                    LOGI("Vulkan initialization completed");
                } catch (const std::exception& e) {
                    LOGE("Failed to initialize Vulkan: %s", e.what());
                }
            }
            break;
            
        case APP_CMD_TERM_WINDOW:
            LOGI("APP_CMD_TERM_WINDOW - Cleaning up Vulkan");
            if (vulkanApp != nullptr) {
                vulkanApp->cleanup();
            }
            break;
            
        case APP_CMD_GAINED_FOCUS:
            LOGI("APP_CMD_GAINED_FOCUS - App gained focus");
            // Resume game logic if needed
            break;
            
        case APP_CMD_LOST_FOCUS:
            LOGI("APP_CMD_LOST_FOCUS - App lost focus");
            // Pause game logic if needed
            break;
            
        case APP_CMD_DESTROY:
            LOGI("APP_CMD_DESTROY - App is being destroyed");
            if (vulkanApp != nullptr) {
                delete vulkanApp;
                app->userData = nullptr;
                g_VulkanApp = nullptr;
            }
            break;
            
        case APP_CMD_PAUSE:
            LOGI("APP_CMD_PAUSE - App paused");
            break;
            
        case APP_CMD_RESUME:
            LOGI("APP_CMD_RESUME - App resumed");
            break;
            
        case APP_CMD_CONFIG_CHANGED:
            LOGI("APP_CMD_CONFIG_CHANGED - Configuration changed");
            break;
            
        case APP_CMD_LOW_MEMORY:
            LOGI("APP_CMD_LOW_MEMORY - Low memory warning");
            // Free up memory if possible
            break;
    }
}

// Handle input events
static int32_t handle_input(android_app* app, AInputEvent* event) {
    VulkanApplication* vulkanApp = (VulkanApplication*)app->userData;
    
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY) {
        int32_t action = AKeyEvent_getAction(event);
        int32_t keycode = AKeyEvent_getKeyCode(event);
        
        if (action == AKEY_EVENT_ACTION_DOWN) {
            LOGI("Key pressed: %d", keycode);
            
            // Handle back button
            if (keycode == AKEYCODE_BACK) {
                // Signal that we want to exit
                ANativeActivity_finish(app->activity);
                return 1;
            }
            
            // Handle other keys for game controls
            switch (keycode) {
                case AKEYCODE_DPAD_UP:
                    // Move forward/up
                    if (vulkanApp) {
                        // vulkanApp->handleInput(KEY_UP);
                    }
                    break;
                case AKEYCODE_DPAD_DOWN:
                    // Move backward/down
                    if (vulkanApp) {
                        // vulkanApp->handleInput(KEY_DOWN);
                    }
                    break;
                case AKEYCODE_DPAD_LEFT:
                    // Move left
                    if (vulkanApp) {
                        // vulkanApp->handleInput(KEY_LEFT);
                    }
                    break;
                case AKEYCODE_DPAD_RIGHT:
                    // Move right
                    if (vulkanApp) {
                        // vulkanApp->handleInput(KEY_RIGHT);
                    }
                    break;
                case AKEYCODE_SPACE:
                    // Jump/action
                    if (vulkanApp) {
                        // vulkanApp->handleInput(KEY_SPACE);
                    }
                    break;
            }
        }
        
    } else if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        int32_t action = AMotionEvent_getAction(event);
        size_t pointerCount = AMotionEvent_getPointerCount(event);
        
        // Handle touch events
        for (size_t i = 0; i < pointerCount; i++) {
            float x = AMotionEvent_getX(event, i);
            float y = AMotionEvent_getY(event, i);
            
            int32_t actionMasked = action & AMOTION_EVENT_ACTION_MASK;
            
            switch (actionMasked) {
                case AMOTION_EVENT_ACTION_DOWN:
                case AMOTION_EVENT_ACTION_POINTER_DOWN:
                    LOGI("Touch down at: %.1f, %.1f", x, y);
                    if (vulkanApp) {
                        // vulkanApp->handleTouch(TouchType::DOWN, x, y, i);
                    }
                    break;
                    
                case AMOTION_EVENT_ACTION_UP:
                case AMOTION_EVENT_ACTION_POINTER_UP:
                    LOGI("Touch up at: %.1f, %.1f", x, y);
                    if (vulkanApp) {
                        // vulkanApp->handleTouch(TouchType::UP, x, y, i);
                    }
                    break;
                    
                case AMOTION_EVENT_ACTION_MOVE:
                    // Handle touch movement
                    if (vulkanApp) {
                        // vulkanApp->handleTouch(TouchType::MOVE, x, y, i);
                    }
                    break;
            }
        }
        
        return 1; // Handled the touch event
    }
    
    return 0;
}

// Frame rate limiter
static void limitFrameRate() {
    using namespace std::chrono;
    
    static high_resolution_clock::time_point lastFrameTime = high_resolution_clock::now();
    static const double frameTime = 1.0 / 60.0; // 60 FPS
    
    auto currentTime = high_resolution_clock::now();
    duration<double> elapsed = currentTime - lastFrameTime;
    
    // If we're running too fast, sleep a bit
    if (elapsed.count() < frameTime) {
        auto sleepTime = duration_cast<milliseconds>(
            duration<double>(frameTime - elapsed.count())
        );
        std::this_thread::sleep_for(sleepTime);
    }
    
    lastFrameTime = high_resolution_clock::now();
}

void android_main(struct android_app* app) {
    LOGI("Android main started");
    
    // Set the app to not destroy the activity on configuration changes
    app->onAppCmd = handle_cmd;
    app->onInputEvent = handle_input;
    
    try {
        // Create Vulkan application instance
        g_VulkanApp = new VulkanApplication();
        app->userData = g_VulkanApp;
        
        LOGI("Vulkan application instance created");
        
    } catch (const std::exception& e) {
        LOGE("Failed to create Vulkan application: %s", e.what());
        return;
    }
    
    // Main game loop
    while (true) {
        int events;
        android_poll_source* source;
        
        // Process all pending events with non-blocking poll
        int result = ALooper_pollAll(0, nullptr, &events, (void**)&source);
        
        if (result >= 0) {
            if (source != nullptr) {
                source->process(app, source);
            }
        }
        
        // Check if we're exiting
        if (app->destroyRequested != 0) {
            LOGI("App destroy requested - exiting main loop");
            break;
        }
        
        // If we have a valid Vulkan app and window, draw frames
        if (g_VulkanApp != nullptr && app->window != nullptr) {
            try {
                g_VulkanApp->drawFrame();
                
                // Limit frame rate to save battery
                limitFrameRate();
                
            } catch (const std::exception& e) {
                LOGE("Error in drawFrame: %s", e.what());
            }
        } else {
            // No window yet, sleep to avoid busy waiting
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }
    
    LOGI("Android main ending");
    
    // Cleanup
    if (g_VulkanApp != nullptr) {
        delete g_VulkanApp;
        g_VulkanApp = nullptr;
    }
    
    LOGI("Android main finished");
}
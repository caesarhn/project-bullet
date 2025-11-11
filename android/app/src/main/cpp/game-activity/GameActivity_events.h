#include "GameActivity.h"
#include "GameActivityConstants.h"
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "bullet-game", __VA_ARGS__))

// Callback for input events
int on_input_event(void* userData, AInputEvent* event) {
    GameActivity* activity = (GameActivity*)userData;
    
    if (GameActivity_isKeyEvent(event)) {
        // Handle key event
        int32_t action = GameActivity_getKeyEventAction(event);
        int32_t keycode = GameActivity_getKeyEventKeyCode(event);
        
        if (action == AKEY_EVENT_ACTION_DOWN) {
            LOGI("Key pressed: %d", keycode);
            
            if (keycode == AKEYCODE_BACK) {
                // Handle back button
                GameActivity_finish(activity);
                return 1;
            }
        }
        
    } else if (GameActivity_isMotionEvent(event)) {
        // Handle motion event (touch)
        int32_t action = GameActivity_getMotionEventAction(event);
        size_t pointerCount = GameActivity_getMotionEventPointerCount(event);
        
        for (size_t i = 0; i < pointerCount; i++) {
            float x = GameActivity_getMotionEventX(event, i);
            float y = GameActivity_getMotionEventY(event, i);
            
            if (action == AMOTION_EVENT_ACTION_DOWN || 
                action == AMOTION_EVENT_ACTION_POINTER_DOWN) {
                LOGI("Touch down at: %.1f, %.1f", x, y);
            } else if (action == AMOTION_EVENT_ACTION_UP ||
                      action == AMOTION_EVENT_ACTION_POINTER_UP) {
                LOGI("Touch up at: %.1f, %.1f", x, y);
            } else if (action == AMOTION_EVENT_ACTION_MOVE) {
                // Handle touch movement
            }
        }
    }
    
    return 0;
}

// Callback for window creation
void on_native_window_created(void* userData, GameActivityWindow* window) {
    LOGI("Window created: %dx%d", window->width, window->height);
    // Initialize your graphics here (OpenGL, Vulkan, etc.)
}

void on_native_window_destroyed(void* userData, GameActivityWindow* window) {
    LOGI("Window destroyed");
    // Cleanup your graphics here
}

void android_main(struct android_app* app) {
    GameActivity activity = {};
    
    // Set up callbacks
    activity.instance = &activity;
    activity.onInputEvent = on_input_event;
    activity.onNativeWindowCreated = on_native_window_created;
    activity.onNativeWindowDestroyed = on_native_window_destroyed;
    
    // Initialize GameActivity
    GameActivity_create(&activity, app);
    
    LOGI("GameActivity initialized");
    
    // Main game loop
    while (true) {
        // Process all pending events
        int events;
        android_poll_source* source;
        
        int result = ALooper_pollAll(0, nullptr, &events, (void**)&source);
        if (result >= 0) {
            if (source != nullptr) {
                source->process(app, source);
            }
        }
        
        // Check if we should exit
        if (app->destroyRequested != 0) {
            LOGI("Exiting game");
            GameActivity_destroy(&activity);
            return;
        }
        
        // Your game rendering and logic here
        // renderFrame();
    }
}
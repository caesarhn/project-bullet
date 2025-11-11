/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <android/configuration.h>
#include <android/input.h>
#include <android/native_window.h>
#include <jni.h>

#include "GameActivityConstants.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct GameActivity;
struct GameActivityWindow;
struct GameTextInput;

// Callback function types
typedef void (*GameActivityOnCreateFunc)(void* instance, void* savedState, size_t savedStateSize);
typedef void (*GameActivityOnDestroyFunc)(void* instance);
typedef void (*GameActivityOnStartFunc)(void* instance);
typedef void (*GameActivityOnResumeFunc)(void* instance);
typedef void (*GameActivityOnSaveInstanceStateFunc)(void* instance, void* outState, size_t* outSize);
typedef void (*GameActivityOnPauseFunc)(void* instance);
typedef void (*GameActivityOnStopFunc)(void* instance);
typedef void (*GameActivityOnConfigurationChangedFunc)(void* instance);
typedef void (*GameActivityOnTrimMemoryFunc)(void* instance, int level);
typedef void (*GameActivityOnWindowFocusChangedFunc)(void* instance, int hasFocus);
typedef void (*GameActivityOnNativeWindowCreatedFunc)(void* instance, struct GameActivityWindow* window);
typedef void (*GameActivityOnNativeWindowResizedFunc)(void* instance, struct GameActivityWindow* window);
typedef void (*GameActivityOnNativeWindowRedrawNeededFunc)(void* instance, struct GameActivityWindow* window);
typedef void (*GameActivityOnNativeWindowDestroyedFunc)(void* instance, struct GameActivityWindow* window);

// Input callback
typedef int (*GameActivityOnInputEventFunc)(void* instance, AInputEvent* event);

// Main GameActivity structure
typedef struct GameActivity {
    // Java VM and JNI environment
    JavaVM* javaVM;
    JNIEnv* env;
    
    // Java activity object
    jobject javaGameActivity;
    
    // Native activity callbacks
    void* instance; // User data pointer
    
    // Lifecycle callbacks
    GameActivityOnCreateFunc onCreate;
    GameActivityOnDestroyFunc onDestroy;
    GameActivityOnStartFunc onStart;
    GameActivityOnResumeFunc onResume;
    GameActivityOnSaveInstanceStateFunc onSaveInstanceState;
    GameActivityOnPauseFunc onPause;
    GameActivityOnStopFunc onStop;
    GameActivityOnConfigurationChangedFunc onConfigurationChanged;
    GameActivityOnTrimMemoryFunc onTrimMemory;
    GameActivityOnWindowFocusChangedFunc onWindowFocusChanged;
    
    // Window callbacks
    GameActivityOnNativeWindowCreatedFunc onNativeWindowCreated;
    GameActivityOnNativeWindowResizedFunc onNativeWindowResized;
    GameActivityOnNativeWindowRedrawNeededFunc onNativeWindowRedrawNeeded;
    GameActivityOnNativeWindowDestroyedFunc onNativeWindowDestroyed;
    
    // Input callback
    GameActivityOnInputEventFunc onInputEvent;
    
    // Current window
    struct GameActivityWindow* window;
    
    // Configuration
    AConfiguration* config;
    
    // Text input
    struct GameTextInput* textInputState;
    
    // Internal state - do not access directly
    void* internalData;
} GameActivity;

// GameActivityWindow structure
typedef struct GameActivityWindow {
    ANativeWindow* nativeWindow;
    int32_t format;
    int32_t width;
    int32_t height;
} GameActivityWindow;

// Function declarations

/**
 * Initialize a GameActivity from the given Android app state.
 */
void GameActivity_create(GameActivity* activity, void* appState);

/**
 * Destroy and cleanup a GameActivity.
 */
void GameActivity_destroy(GameActivity* activity);

/**
 * Finish the activity.
 */
void GameActivity_finish(GameActivity* activity);

/**
 * Set window flags.
 */
void GameActivity_setWindowFlags(GameActivity* activity, int32_t values, int32_t mask);

/**
 * Clear window flags.
 */
void GameActivity_clearWindowFlags(GameActivity* activity, int32_t values, int32_t mask);

/**
 * Set window format.
 */
void GameActivity_setWindowFormat(GameActivity* activity, int32_t format);

/**
 * Show the soft keyboard.
 */
void GameActivity_showSoftInput(GameActivity* activity);

/**
 * Hide the soft keyboard.
 */
void GameActivity_hideSoftInput(GameActivity* activity);

/**
 * Get the content area in which the game should render.
 */
void GameActivity_getContentRect(GameActivity* activity, ARect* outRect);

/**
 * Get the GameTextInput state for this activity.
 */
struct GameTextInput* GameActivity_getTextInput(GameActivity* activity);

// Input event functions
int32_t GameActivity_getKeyEventAction(AInputEvent* event);
int32_t GameActivity_getKeyEventKeyCode(AInputEvent* event);
int32_t GameActivity_getKeyEventRepeatCount(AInputEvent* event);
int32_t GameActivity_getKeyEventMetaState(AInputEvent* event);
int64_t GameActivity_getKeyEventEventTime(AInputEvent* event);
int64_t GameActivity_getKeyEventDownTime(AInputEvent* event);

// Motion event functions
int32_t GameActivity_getMotionEventAction(AInputEvent* event);
int32_t GameActivity_getMotionEventMetaState(AInputEvent* event);
int32_t GameActivity_getMotionEventButtonState(AInputEvent* event);
int32_t GameActivity_getMotionEventFlags(AInputEvent* event);
float GameActivity_getMotionEventXOffset(AInputEvent* event);
float GameActivity_getMotionEventYOffset(AInputEvent* event);
float GameActivity_getMotionEventXPrecision(AInputEvent* event);
float GameActivity_getMotionEventYPrecision(AInputEvent* event);
int64_t GameActivity_getMotionEventEventTime(AInputEvent* event);
int64_t GameActivity_getMotionEventDownTime(AInputEvent* event);
size_t GameActivity_getMotionEventPointerCount(AInputEvent* event);
int32_t GameActivity_getMotionEventPointerId(AInputEvent* event, size_t pointerIndex);
float GameActivity_getMotionEventX(AInputEvent* event, size_t pointerIndex);
float GameActivity_getMotionEventY(AInputEvent* event, size_t pointerIndex);
float GameActivity_getMotionEventPressure(AInputEvent* event, size_t pointerIndex);
float GameActivity_getMotionEventSize(AInputEvent* event, size_t pointerIndex);
float GameActivity_getMotionEventTouchMajor(AInputEvent* event, size_t pointerIndex);
float GameActivity_getMotionEventTouchMinor(AInputEvent* event, size_t pointerIndex);
float GameActivity_getMotionEventToolMajor(AInputEvent* event, size_t pointerIndex);
float GameActivity_getMotionEventToolMinor(AInputEvent* event, size_t pointerIndex);
float GameActivity_getMotionEventOrientation(AInputEvent* event, size_t pointerIndex);
int32_t GameActivity_getMotionEventAxisValue(AInputEvent* event, int32_t axis, size_t pointerIndex);
int32_t GameActivity_getMotionEventHistorySize(AInputEvent* event);
int64_t GameActivity_getMotionEventHistoricalEventTime(AInputEvent* event, size_t historyIndex);
float GameActivity_getMotionEventHistoricalX(AInputEvent* event, size_t pointerIndex, size_t historyIndex);
float GameActivity_getMotionEventHistoricalY(AInputEvent* event, size_t pointerIndex, size_t historyIndex);
float GameActivity_getMotionEventHistoricalPressure(AInputEvent* event, size_t pointerIndex, size_t historyIndex);
float GameActivity_getMotionEventHistoricalSize(AInputEvent* event, size_t pointerIndex, size_t historyIndex);
float GameActivity_getMotionEventHistoricalTouchMajor(AInputEvent* event, size_t pointerIndex, size_t historyIndex);
float GameActivity_getMotionEventHistoricalTouchMinor(AInputEvent* event, size_t pointerIndex, size_t historyIndex);
float GameActivity_getMotionEventHistoricalToolMajor(AInputEvent* event, size_t pointerIndex, size_t historyIndex);
float GameActivity_getMotionEventHistoricalToolMinor(AInputEvent* event, size_t pointerIndex, size_t historyIndex);
float GameActivity_getMotionEventHistoricalOrientation(AInputEvent* event, size_t pointerIndex, size_t historyIndex);
float GameActivity_getMotionEventHistoricalAxisValue(AInputEvent* event, int32_t axis, size_t pointerIndex, size_t historyIndex);

#ifdef __cplusplus
}
#endif
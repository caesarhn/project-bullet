#!/bin/bash

echo "Building Vulkan Android application..."

cd android

# Clean previous build
./gradlew clean

# Build debug APK
./gradlew assembleDebug

if [ $? -eq 0 ]; then
    echo "Build successful!"
    
    # Install to device
    adb install -r app/build/outputs/apk/debug/app-debug.apk
    
    # Run the app
    adb shell am start -n com.example.vulkanapp/android.app.NativeActivity
    
    # Show logs
    echo "Showing logs... (Press Ctrl+C to stop)"
    adb logcat -s VulkanApp:D DEBUG:I
else
    echo "Build failed!"
    exit 1
fi
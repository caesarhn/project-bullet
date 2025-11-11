#!/bin/bash
# Monitor Vulkan app logs
adb logcat -c
adb logcat -s VulkanApp:D DEBUG:I VULKAN:*
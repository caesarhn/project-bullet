cmake_minimum_required(VERSION 3.18.1)

project("vulkan-android")

find_library(log-lib log)
find_library(android-lib android)

include_directories(
    ${CMAKE_SOURCE_DIR}/../../../../../imgui-master
    ${CMAKE_SOURCE_DIR}/../../../../../glm-master
    ${CMAKE_SOURCE_DIR}/../../../../../lib
)

include_directories(${ANDROID_NDK}/sources/android/native_app_glue)
find_library(android_LIBRARY android)
find_library(log_LIBRARY log)

# Source files
add_library(
    vulkan-app
    SHARED
    android_main.cpp
    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/init.cpp
    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/draw.cpp
    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/variable.cpp

    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/buffer.cpp
    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/draw.cpp
    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/init.cpp
    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/pool.cpp
    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/texture.cpp
    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/variable.cpp
    ${CMAKE_SOURCE_DIR}/../../../../../lib/vulkan/vulkan_helper.cpp
    
    ${CMAKE_SOURCE_DIR}/../../../../../lib/app/app.cpp

    ${CMAKE_SOURCE_DIR}/../../../../../lib/char/char.cpp
)

# Include directories
target_include_directories(vulkan-app PRIVATE
    ${CMAKE_SOURCE_DIR}/../../../../lib
)

# Link libraries
target_link_libraries(vulkan-app
    android
    log
    vulkan
)

# C++ standard
set_target_properties(vulkan-app PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
cmake_minimum_required(VERSION 3.10)  # Versi minimum CMake
project(GreatWall_0.0.1)                    # Nama proyek

# Pilih compiler
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

# Tentukan lokasi Vulkan SDK secara manual
if(WIN32)
    message(STATUS "Compiling for Windows")
    set(VULKAN_SDK "C:/VulkanSDK/1.4.304.1")  # Ganti dengan path Vulkan SDK yang sesuai
    # Tambahkan path header Vulkan
    include_directories(
        ${VULKAN_SDK}/Include
        "GLFW-VC-22/include"
        "imgui-master"
        "glm-master"
        "lib"
    )
    # Tambahkan path library
    link_directories(
        ${VULKAN_SDK}/Lib
        "GLFW-VC-22/lib"
    )
    set(LIBS vulkan-1 glfw3)

elseif(UNIX)
    message(STATUS "Compiling for Linux")
    
    # Temukan Vulkan dan GLFW di Linux
    find_package(Vulkan REQUIRED)
    find_package(glfw3 REQUIRED)

    include_directories(
        /home/caesar/vulkansdk/x86_64/include
        /usr/include
        /usr/local/include
        imgui-master
        glm-master
        lib
    )
        
    link_directories(
        /usr/lib
        /usr/local/lib
        /home/caesar/vulkansdk/x86_64/lib
    )
    set(LIBS Vulkan::Vulkan glfw)
endif()

set(CMAKE_CXX_STANDARD 17)            # Gunakan C++17
set(CMAKE_CXX_STANDARD_REQUIRED True) 

add_executable(
    vulkan_new 
    main.cpp 
    lib/ui.cpp 
    imgui-master/imgui.cpp
    imgui-master/imgui_draw.cpp
    imgui-master/imgui_tables.cpp
    imgui-master/imgui_widgets.cpp
    imgui-master/imgui_demo.cpp
    imgui-master/backends/imgui_impl_vulkan.cpp
    imgui-master/backends/imgui_impl_glfw.cpp
)  # Nama output dan source files

# Hubungkan dengan library Vulkan
target_link_libraries(vulkan_new PRIVATE ${LIBS})
# target_link_libraries(vulkan_new PRIVATE 
#     vulkan-1
#     glfw3
# )

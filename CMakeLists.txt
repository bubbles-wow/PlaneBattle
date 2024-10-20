# 主项目的 CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(PlaneProject LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 配置输出目录
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin/Debug/x64)
    else()  # 32-bit
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin/Debug/x86)
    endif()
else()
    if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin/Release/x64)
    else()  # 32-bit
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin/Release/x86)
    endif()
endif()

# 添加子目录（Logger 和 Plane 项目）
add_subdirectory(Logger)
add_subdirectory(Plane)
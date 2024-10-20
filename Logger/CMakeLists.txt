# Logger/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(Logger LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 收集 Logger 项目的源码和头文件
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# 在编译 DLL 时
add_definitions(-DLOGGER_EXPORTS)

# 添加 Logger 库（静态或动态）
add_library(Logger SHARED ${SOURCES} ${HEADERS})

# 设置头文件的包含路径，供其他项目使用
target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 平台相关配置
if(MSVC)
    add_compile_definitions(UNICODE _UNICODE)  # 确保启用 Unicode 支持
    # 为 Debug 配置添加特定编译选项
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_options(/W4 /permissive- /Zc:__cplusplus)
    # 为 Release 配置添加特定编译选项
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_compile_options(/W3 /permissive- /Zc:__cplusplus)
    endif()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")  # Release
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")  # Debug
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
else()
    add_compile_options(-Wall -Wextra -pedantic)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()

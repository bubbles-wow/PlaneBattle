cmake_minimum_required(VERSION 3.8)
project(Plane LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置包含路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/easyx/include
    ${CMAKE_SOURCE_DIR}/external/fmod/include
)

# 根据当前平台选择库目录
if(CMAKE_SIZEOF_VOID_P EQUAL 8)  # 64-bit
    set(EASYX_LIB_DIR ${CMAKE_SOURCE_DIR}/external/easyx/lib/x64)
    set(FMOD_LIB_DIR ${CMAKE_SOURCE_DIR}/external/fmod/lib/x64)
else()  # 32-bit
    set(EASYX_LIB_DIR ${CMAKE_SOURCE_DIR}/external/easyx/lib/x86)
    set(FMOD_LIB_DIR ${CMAKE_SOURCE_DIR}/external/fmod/lib/x86)
endif()

# 收集源文件和头文件
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.rc)

# 链接路径
link_directories(${EASYX_LIB_DIR})
link_directories(${FMOD_LIB_DIR})

# 创建可执行文件目标
add_executable(Plane ${SOURCES} ${HEADERS} ${RESOURCES})

# 链接库到当前项目
target_link_libraries(Plane PRIVATE Logger)
target_link_libraries(Plane PRIVATE $<IF:$<CONFIG:Debug>,fmodL_vc,fmod_vc>)

# 复制 Logger.dll 到可执行文件目录
add_custom_command(
    TARGET Plane POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:Logger>  # Logger.dll 的路径
	$<TARGET_FILE_DIR:Plane>  # Plane.exe 的目录
)

add_custom_command(
    TARGET Plane POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${FMOD_LIB_DIR}/$<IF:$<CONFIG:Debug>,fmodL.dll,fmod.dll>
	$<TARGET_FILE_DIR:Plane>
)

# 定义资源路径
set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(OUTPUT_DIR $<TARGET_FILE_DIR:Plane>/res)

# 找到所有资源文件（如 png 和 ttf）
file(GLOB_RECURSE RESOURCES 
    ${RESOURCE_DIR}/*.png 
    ${RESOURCE_DIR}/*.ttf
)

# 为 Plane 添加构建后命令，在构建完成后复制资源
add_custom_command(
    TARGET Plane POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_DIR} ${OUTPUT_DIR}
    COMMENT "Copying resource files to output directory"
)

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

# 设置 DPI 感知
if(WIN32)
    add_definitions(-DUNICODE -D_ENABLE_DPI_AWARENESS)
endif()

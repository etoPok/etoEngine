cmake_minimum_required(VERSION 3.10)

project(helloTriangle VERSION 1.0)

# specify the c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(include/helloTriangleConfig.h.in include/helloTriangleConfig.h)

# check VULKAN_SDK
if(NOT DEFINED ENV{VULKAN_SDK})
    message(FATAL_ERROR "VULKAN_SDK environment variable not set")
endif()

# set VULKAN_SDK
set(VULKAN_SDK $ENV{VULKAN_SDK})

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${VULKAN_SDK}/include
    /usr/local/include
)

target_link_directories(${PROJECT_NAME} PUBLIC
    ${VULKAN_SDK}/lib
    /usr/local/lib
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    vulkan
)

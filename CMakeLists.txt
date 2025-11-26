cmake_minimum_required(VERSION 3.16)
project(OurTube LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME} WIN32
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

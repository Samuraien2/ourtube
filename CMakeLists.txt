cmake_minimum_required(VERSION 3.16)
project(ourtube VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

if(WIN32)
    set(TARGET_NAME "OurTube")
else()
    set(TARGET_NAME "ourtube")
endif()

add_executable(${TARGET_NAME} WIN32
    src/main.cpp
)

if(WIN32)
    set_target_properties(${TARGET_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Widgets)

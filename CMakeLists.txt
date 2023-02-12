cmake_minimum_required(VERSION 3.5)

project(modify_shape LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("${PROJECT_SOURCE_DIR}/inc")
include_directories("${PROJECT_SOURCE_DIR}/inc/math")

file(GLOB CPP1 "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB CPP2 "${PROJECT_SOURCE_DIR}/src/math/*.cpp")


add_executable(${PROJECT_NAME}  main.cpp ${CPP1} ${CPP2})

target_link_libraries(${PROJECT_NAME} fltk)

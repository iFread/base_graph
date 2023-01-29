cmake_minimum_required(VERSION 3.5)

project(modify_shape LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("${PROJECT_SOURCE_DIR}/inc")

file(GLOB CPP1 "${PROJECT_SOURCE_DIR}/src/*.cpp")



add_executable(${PROJECT_NAME}  main.cpp ${CPP1})
target_link_libraries(${PROJECT_NAME} fltk)

cmake_minimum_required(VERSION 3.5)

project(simple_cad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -Wall -O0 -g" )

include_directories("${PROJECT_SOURCE_DIR}/inc")
include_directories("${PROJECT_SOURCE_DIR}/inc/math")
include_directories("${PROJECT_SOURCE_DIR}/inc/algorithm")

file(GLOB CPP1 "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB CPP2 "${PROJECT_SOURCE_DIR}/src/math/*.cpp")


add_executable(${PROJECT_NAME}  main.cpp ${CPP1} ${CPP2})

target_link_libraries(${PROJECT_NAME} fltk)

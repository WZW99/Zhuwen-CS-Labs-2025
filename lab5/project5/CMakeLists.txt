cmake_minimum_required(VERSION 3.20)
project(collections)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB HEADERS "*.h")

add_library(collections INTERFACE)
target_sources(collections INTERFACE ${HEADERS})
target_include_directories(collections INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(collections_executable main.cpp)
target_link_libraries(collections_executable collections)

cmake_minimum_required(VERSION 3.20)
set(project "Stack")
project(${project})

set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Stack.h)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${project} INTERFACE ${HEADERS})
if(ENABLE_DEBUG)
    target_compile_options(${project} INTERFACE -g)
endif()

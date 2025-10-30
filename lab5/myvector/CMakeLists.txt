cmake_minimum_required(VERSION 3.20)

set(project "collections")
project(${project})

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/MyVector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MySet.h
)

add_library(${project} INTERFACE)

target_sources(${project} INTERFACE ${HEADERS})

target_include_directories(${project} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

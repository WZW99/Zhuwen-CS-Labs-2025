cmake_minimum_required(VERSION 3.20)
set(project "Persons")
project(${project})

set(SOURCES
    Person.cpp Employee.cpp Worker.cpp Engineer.cpp
)
set(HEADERS
    Person.h Employee.h Worker.h Engineer.h
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${project} STATIC ${SOURCES} ${HEADERS})
if(ENABLE_DEBUG)
    target_compile_options(${project} PRIVATE -g)
endif()

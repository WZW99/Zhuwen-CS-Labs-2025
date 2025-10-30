cmake_minimum_required(VERSION 3.23)

set(project "lab2")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        main.cpp)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project} /home/zhuwen/Zhuwen-CS-Labs-2025/lab2/filmoteka/build/libfilmoteka.a
                                 /home/zhuwen/Zhuwen-CS-Labs-2025/lab2/planet/build/libplanet.a)
